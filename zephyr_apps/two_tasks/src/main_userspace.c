#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 2048
#define PRIORITY  7

static void check_mode(const char *task_name)
{
	if (k_is_user_context()) {
		printk("%s [API] USER MODE (nao privilegiado)\n", task_name);
	} else {
		printk("%s [API] KERNEL MODE (privilegiado)\n", task_name);
	}
}

void task_a_entry(void *p1, void *p2, void *p3)
{
	while (1) {
		check_mode("[TASK A]");
		printk("[TASK A] a correr\n\n");
		k_sleep(K_MSEC(2000));
	}
}

void task_b_entry(void *p1, void *p2, void *p3)
{
	while (1) {
		check_mode("[TASK B]");
		printk("[TASK B] a correr\n\n");
		k_sleep(K_MSEC(5000));
	}
}

K_THREAD_DEFINE(task_a_id, STACKSIZE, task_a_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_b_id, STACKSIZE, task_b_entry, NULL, NULL, NULL, PRIORITY, K_USER, 0);
