#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* FreeRTOS: ambas as tasks em M-mode, adversarial escreve na flag global e chama funcao da TaskA
   Zephyr:   ambas as tasks em U-mode, adversarial tenta escrever na flag -> Store Access Fault */

#define STACKSIZE 4096
#define PRIORITY  7

static volatile int chamado_por_adversarial = 0;

void task_a_entry(void *p1, void *p2, void *p3)
{
    for (;;) {
        printk("[TASK A] a correr normalmente\n");
        k_sleep(K_MSEC(1000));
    }
}

void task_adv_entry(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(3000));
    printk("[ADV] a tentar modificar chamado_por_adversarial (global do kernel)...\n");

    chamado_por_adversarial = 1;  /* STORE ACCESS FAULT — global em espaco do kernel */

    /* linha abaixo nunca executa */
    void (*fn)(void *, void *, void *) = task_a_entry;
    fn(NULL, NULL, NULL);
    chamado_por_adversarial = 0;
}

K_THREAD_DEFINE(task_a_id,   STACKSIZE, task_a_entry,   NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_adv_id, STACKSIZE, task_adv_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);
