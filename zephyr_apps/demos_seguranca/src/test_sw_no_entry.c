#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*
 * TESTE 2 — SW para regiao sem entrada PMP (default deny)
 *
 * A thread em U-mode faz um store explícito para um global do kernel.
 * Esse endereço não tem nenhuma entrada PMP para U-mode.
 * ESPERADO: mcause=7 (Store/AMO access fault)
 * SE VIER 5 (Load access fault) → o CVA6 está a reportar errado no path
 * "sem entrada" — confirma o bug independente do tipo de acesso.
 */

#define STACKSIZE 2048
#define PRIORITY  7

static volatile int kernel_var = 0;

void test_thread(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(500));

    uintptr_t addr = (uintptr_t)&kernel_var;
    int valor = 0xDEAD;

    printk("[TESTE 2] SW para kernel_var @ 0x%08x (sem entrada PMP)...\n", (uint32_t)addr);

    __asm__ volatile("sw %0, 0(%1)" : : "r"(valor), "r"(addr) : "memory");

    printk("[TESTE 2] store ok  <-- nao devia chegar aqui\n");
}

K_THREAD_DEFINE(test_id, STACKSIZE, test_thread, NULL, NULL, NULL, PRIORITY, K_USER, 0);
