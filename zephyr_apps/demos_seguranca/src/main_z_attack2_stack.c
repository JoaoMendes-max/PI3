#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/app_memory/app_memdomain.h>
#include <zephyr/sys/libc-hooks.h>

/*
 * ATAQUE 2 — ESCRITA NA STACK DE OUTRA TASK (Zephyr)
 *
 * Task A tem uma password local (na sua stack) e escreve o seu endereço em
 * leaked_addr — variável global em shared_part, acessível a ambas as tasks.
 * Task ADV lê o endereço via shared_part e tenta escrever na stack da Task A.
 *
 * RESULTADO ESPERADO:
 *   [MAIN] a configurar dominios...
 *   [MAIN] domA configurado
 *   [MAIN] domB configurado
 *   [MAIN] threads arrancadas
 *   [TASK A] a correr em U-mode
 *   [TASK A] password em stack: 0x8008XXXX
 *   [TASK A] leaked_addr escrito: 0x8008XXXX
 *   [TASK A] password OK: 1234
 *   [ADV] a correr em U-mode, a aguardar 3s...
 *   [ADV] leaked_addr lido: 0x8008XXXX
 *   [ADV] a tentar escrever na stack da Task A...
 *   mcause: 7, Store/AMO access fault   <- PMP bloqueia
 *
 * CONTRASTE COM FREERTOS (M-mode):
 *   FreeRTOS / M-mode → sem PMP activo, a adversarial escreve directamente
 *                        na stack da Task A — password CORROMPIDA.
 *   Zephyr / U-mode   → Store Access Fault (mcause: 7) ao tentar escrever
 *                        na stack de outra task. PMP entry dedicada por thread.
 */

#define STACKSIZE 2048
#define PRIORITY  7

K_APPMEM_PARTITION_DEFINE(shared_part);

/*
 * Dois campos em shared_part — total 8 bytes = minimo NAPOT RISC-V (2^3).
 * Com apenas 4 bytes (um uint32_t) o PMP NAPOT nao consegue criar uma
 * entrada valida e o acesso em U-mode falha.
 */
K_APP_DMEM(shared_part) volatile uint32_t leaked_addr = 0;
K_APP_DMEM(shared_part) volatile uint32_t shared_ready = 0;

static struct k_mem_domain domA;
static struct k_mem_domain domB;

struct k_thread task_a_thread;
K_THREAD_STACK_DEFINE(task_a_stack, STACKSIZE);

struct k_thread task_adv_thread;
K_THREAD_STACK_DEFINE(task_adv_stack, STACKSIZE);

/* ------------------------------------------------------------------ */

void task_a_entry(void *p1, void *p2, void *p3)
{
    printk("[TASK A] a correr em U-mode\n");

    volatile int password = 1234;

    printk("[TASK A] password em stack: 0x%08x\n", (uint32_t)&password);

    leaked_addr = (uint32_t)&password;
    shared_ready = 1;
    printk("[TASK A] leaked_addr escrito: 0x%08x\n", leaked_addr);

    for (;;) {
        if (password == 1234) {
            printk("[TASK A] password OK: %d\n", password);
        } else {
            printk("[TASK A] password CORROMPIDA: 0x%08x  <-- ataque!\n",
                   (uint32_t)password);
        }
        k_sleep(K_MSEC(1000));
    }
}

/* ------------------------------------------------------------------ */

void task_adv_entry(void *p1, void *p2, void *p3)
{
    printk("[ADV] a correr em U-mode, a aguardar leaked_addr...\n");

    /* espera que Task A escreva o endereco via shared_ready */
    while (shared_ready == 0) {
        k_sleep(K_MSEC(100));
    }

    volatile int *ptr = (volatile int *)leaked_addr;

    printk("[ADV] leaked_addr lido: 0x%08x\n", (uint32_t)ptr);
    printk("[ADV] a tentar escrever na stack da Task A...\n");

    /*
     * STORE ACCESS FAULT esperado aqui (mcause: 7):
     * A stack da Task A tem PMP entry exclusiva — Task ADV nao tem acesso.
     * Em FreeRTOS/M-mode esta linha corromperia a password com sucesso.
     */
    *ptr = 0xDEAD;

    printk("[ADV] escrita ok -- proteccao falhou!\n");
}

/* ------------------------------------------------------------------ */

int main(void)
{
    k_tid_t tA, tADV;

    printk("[MAIN] a configurar dominios...\n");

    /*
     * Criar threads suspensas (K_FOREVER) — ainda nao correm.
     * Padrao oficial Zephyr: criar suspensa, configurar dominio, depois start.
     * Garante que o PMP esta pronto antes da primeira instrucao em U-mode.
     */
    tA = k_thread_create(&task_a_thread, task_a_stack, STACKSIZE,
                         task_a_entry, NULL, NULL, NULL,
                         PRIORITY, K_USER, K_FOREVER);

    tADV = k_thread_create(&task_adv_thread, task_adv_stack, STACKSIZE,
                           task_adv_entry, NULL, NULL, NULL,
                           PRIORITY, K_USER, K_FOREVER);

    struct k_mem_partition *parts_a[] = {
#if Z_LIBC_PARTITION_EXISTS
        &z_libc_partition,
#endif
        &shared_part
    };
    struct k_mem_partition *parts_b[] = {
#if Z_LIBC_PARTITION_EXISTS
        &z_libc_partition,
#endif
        &shared_part
    };

    k_mem_domain_init(&domA, ARRAY_SIZE(parts_a), parts_a);
    k_mem_domain_add_thread(&domA, tA);
    printk("[MAIN] domA configurado\n");

    k_mem_domain_init(&domB, ARRAY_SIZE(parts_b), parts_b);
    k_mem_domain_add_thread(&domB, tADV);
    printk("[MAIN] domB configurado\n");

    /* Dominios prontos — so agora arrancar as threads */
    k_thread_start(tA);
    k_thread_start(tADV);

    printk("[MAIN] threads arrancadas\n");
    return 0;
}