#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 2048
#define PRIORITY  7

void task_a_entry(void *p1, void *p2, void *p3)
{
    for (;;) {
        printk("[TASK A] A correr normalmente...\n");
        k_sleep(K_MSEC(1000));
    }
}

void task_adv_entry(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(3000));
    printk("[TESTE 5 STORES] A disparar sequencia de escrita para forcar mcause = 7...\n");

    /*
     * t1: Endereço protegido do kernel
     * Executa 5 instruções sw seguidas no mesmo endereço protegido.
     * Se o hardware roubar o tipo da instrução seguinte, vai apanhar um sw
     * e terá de registar Store Access Fault (mcause = 7).
     */
    __asm__ volatile (
        "li t1, 0x80011000\n\t"

        "sw zero, 0(t1)\n\t"      /* 1º Store -> Onde o PMP vai disparar */
        "sw zero, 0(t1)\n\t"      /* 2º Store */

    );

    printk("[TESTE 5 STORES] Se leres isto, a proteccao falhou.\n");
}

K_THREAD_DEFINE(task_a_id,   STACKSIZE, task_a_entry,   NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_adv_id, STACKSIZE, task_adv_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);