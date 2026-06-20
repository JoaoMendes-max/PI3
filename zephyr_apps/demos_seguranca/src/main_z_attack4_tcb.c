#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

/* FreeRTOS: adversarial corrompe o primeiro campo do TCB (stack pointer) da TaskA -> crash
   Zephyr:   adversarial tenta escrever no struct k_thread da task_a_id -> Store Access Fault */

#define STACKSIZE 2048
#define PRIORITY  7

/* referencia interna criada pelo K_THREAD_DEFINE(task_a_id, ...) abaixo */
extern struct k_thread _k_thread_obj_task_a_id;

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

    volatile uint32_t *tcb = (volatile uint32_t *)&_k_thread_obj_task_a_id;
    printk("[ADV] TCB de Task A em: 0x%08x\n", (uint32_t)tcb);
    printk("[ADV] a tentar corromper stack pointer da Task A...\n");

    tcb[0] = 0xDEADBEEF;  /* STORE ACCESS FAULT — struct k_thread em espaco do kernel */

    printk("[ADV] stack pointer corrompido!\n");  /* nunca executa */
}

K_THREAD_DEFINE(task_a_id,   STACKSIZE, task_a_entry,   NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_adv_id, STACKSIZE, task_adv_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);
