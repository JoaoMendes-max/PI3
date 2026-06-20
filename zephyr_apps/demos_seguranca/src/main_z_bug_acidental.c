#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/*
 * BUG ACIDENTAL — ESCRITA FORA DOS LIMITES (Zephyr)
 *
 * Equivalente ao freertos_demo6_bug_acidental.c.
 *
 * CENÁRIO: Task Buggy tem um array local de 8 bytes mas por engano
 * itera 512 vezes (erro de constante — bug clássico em C embebido).
 * Não é malware — é um programador que escreveu o número errado.
 *
 * RESULTADO ESPERADO (Zephyr / U-mode):
 *   [TASK A] a correr normalmente
 *   [TASK A] a correr normalmente
 *   [BUG]    a escrever config (bug: 512 iteracoes, devia ser 8)...
 *   mcause: 7, Store Access Fault   <- PMP contém o bug dentro da Task Buggy
 *   [TASK A] a correr normalmente   <- Task A não é afectada, continua a correr
 *   ...
 *
 * CONTRASTE COM FREERTOS (freertos_demo6_bug_acidental.c):
 *   FreeRTOS / M-mode → overflow silencioso, dados da Task A corrompidos,
 *                        nenhuma detecção, sistema continua a correr com
 *                        dados errados.
 *   Zephyr / U-mode   → Store Access Fault contém a falha na Task Buggy.
 *                        Task A não é afectada.
 *
 * NOTA: O isolamento aqui não é contra um adversário — é contra um bug.
 * Mostra que PMP/U-mode protege a integridade do sistema mesmo sem
 * intenção maliciosa: uma task com erro não consegue destruir as outras.
 */

#define STACKSIZE 2048
#define PRIORITY  7

void task_a_entry(void *p1, void *p2, void *p3)
{
    for (;;) {
        printk("[TASK A] a correr normalmente\n");
        k_sleep(K_MSEC(1000));
    }
}

void task_buggy_entry(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(3000));

    printk("[BUG] a escrever config (bug: 512 iteracoes, devia ser 8)...\n");

    volatile char config[8];

    /* BUG: programador escreveu 512 em vez de 8 — erro de constante */
    for (volatile int i = 0; i < 512; i++) {
        config[i] = 0;  /* Store Access Fault quando ultrapassa a região PMP da stack */
    }

    printk("[BUG] escrita concluida\n");  /* nunca executa */
}

K_THREAD_DEFINE(task_a_id,     STACKSIZE, task_a_entry,     NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_buggy_id, STACKSIZE, task_buggy_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);
