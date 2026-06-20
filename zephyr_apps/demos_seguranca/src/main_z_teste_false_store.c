//
// Created by mendes on 16/05/26.
//

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
    printk("[TESTE ILEGAL] A disparar Stores em multiplos enderecos proibidos...\n");

    /*
     * Todos estes endereços pertencem ao espaço do kernel (z_interrupt_stacks).
     * São todos 100% ILEGAIS para a Task ADV em U-mode, mas são números diferentes.
     */
    __asm__ volatile (
        "li t1, 0x80011000\n\t"   /* 1º Alvo proibido */
        "li t2, 0x80011004\n\t"   /* 2º Alvo proibido */

        "sw zero, 0(t1)\n\t"      /* 1º Store -> Bate no PMP (mepc deve ser o endereço desta instrução) */
        "sw zero, 0(t2)\n\t"      /* 2º Store -> Instrução mepc + 4 */
    );

    printk("[TESTE ILEGAL] Se leres isto, a proteccao falhou.\n");
}

K_THREAD_DEFINE(task_a_id,   STACKSIZE, task_a_entry,   NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_adv_id, STACKSIZE, task_adv_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);