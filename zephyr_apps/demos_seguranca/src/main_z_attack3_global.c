#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* FreeRTOS: adversarial escreve directamente em variavel global da TaskA -> TaskA ve "CORROMPIDO"
   Zephyr:   adversarial tenta escrever na variavel global -> Store Access Fault */

#define STACKSIZE 2048
#define PRIORITY  7

volatile int dados_task_a = 42;

void task_a_entry(void *p1, void *p2, void *p3)
{
    for (;;) {
        printk("[TASK A] a correr\n");
        k_sleep(K_MSEC(1000));
    }
}

void task_adv_entry(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(3001));
    printk("[ADV] a tentar corromper dados_task_a \n");

    dados_task_a = 0xDEAD;  /* STORE ACCESS FAULT — global em espaco do kernel */

    printk("[ADV] dados corrompidos!\n");  /* nunca executa */
}

K_THREAD_DEFINE(task_a_id,   STACKSIZE, task_a_entry,   NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_adv_id, STACKSIZE, task_adv_entry, NULL, NULL, NULL, 6, K_USER, 0);
