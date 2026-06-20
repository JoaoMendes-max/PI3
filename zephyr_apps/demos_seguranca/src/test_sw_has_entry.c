#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*
 * TESTE 3 — SW para regiao COM entrada PMP (R|X, sem W)
 *
 * A thread em U-mode faz um store explícito para um endereço do .text
 * (codigo do kernel). Essa região TEM uma entrada PMP activa com R|X,
 * mas SEM W — é um "match com permissão errada".
 *
 * Distingue dois paths no CVA6:
 *   - Path A (sem match):  nenhuma entrada cobre o addr → allow_o=0
 *   - Path B (match+deny): entrada cobre mas W=0       → allow_o=0
 *
 * ESPERADO: mcause=7 (Store/AMO access fault) — ambos os paths devem dar 7.
 * SE TESTE 2 deu 5 e TESTE 3 der 7 → o bug está no path "sem match".
 * SE AMBOS derem 5 (lsu_is_store_i não chega
 * ao pmp_data_if ou é ignorado).
 */

#define STACKSIZE 2048
#define PRIORITY  7

/* Ponteiro para uma função do kernel — endereço em .text, coberto por PMP R|X */
extern void z_riscv_fault(void);

void test_thread(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(500));

    uintptr_t addr = (uintptr_t)z_riscv_fault;
    int valor = 0xDEAD;

    printk("[TESTE 3] SW para .text @ 0x%08x (entrada PMP R|X, sem W)...\n", (uint32_t)addr);

    __asm__ volatile("sw %0, 0(%1)" : : "r"(valor), "r"(addr) : "memory");

    printk("[TESTE 3] store ok  <-- nao devia chegar aqui\n");
}

K_THREAD_DEFINE(test_id, STACKSIZE, test_thread, NULL, NULL, NULL, PRIORITY, K_USER, 0);
