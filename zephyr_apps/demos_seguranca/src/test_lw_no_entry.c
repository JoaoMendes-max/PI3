#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*
 * TESTE 1 — LW de regiao sem entrada PMP (default deny)
 *
 * A thread em U-mode faz um load explícito de um global do kernel.
 * Esse endereço não tem nenhuma entrada PMP para U-mode.
 * ESPERADO: mcause=5 (Load access fault) — baseline de confirmação.
 */

#define STACKSIZE 2048
#define PRIORITY  7

static volatile int kernel_var = 0xABCD1234;

void test_thread(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(500));

    uintptr_t addr = (uintptr_t)&kernel_var;
    volatile int resultado;

    printk("[TESTE 1] LW de kernel_var @ 0x%08x (sem entrada PMP)...\n", (uint32_t)addr);

    __asm__ volatile("lw %0, 0(%1)" : "=r"(resultado) : "r"(addr) : "memory");

    printk("[TESTE 1] resultado: 0x%08x  <-- nao devia chegar aqui\n", resultado);
}

K_THREAD_DEFINE(test_id, STACKSIZE, test_thread, NULL, NULL, NULL, PRIORITY, K_USER, 0);
