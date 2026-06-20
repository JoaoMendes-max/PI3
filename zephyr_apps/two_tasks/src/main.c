#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 2048
#define PRIORITY  7

static void print_privilege_mode(const char *task_name)
{
	uint32_t mstatus;
	__asm__ volatile ("csrr %0, mstatus" : "=r"(mstatus));
	uint32_t mpp = (mstatus >> 11) & 0x3;
	const char *mode = (mpp == 3) ? "M-mode" : (mpp == 1) ? "S-mode" : "U-mode";
	printk("%s [CSR] MPP=%d (%s) mstatus=0x%08x\n", task_name, mpp, mode, mstatus);
}

static void task_a(void *p1, void *p2, void *p3)
{
	while (1) {
		print_privilege_mode("[TASK A]");
		printk("[TASK A] a correr\n\n");
		k_sleep(K_MSEC(2000));
	}
}

static void task_b(void *p1, void *p2, void *p3)
{
	while (1) {
		print_privilege_mode("[TASK B]");
		printk("[TASK B] a correr\n\n");
		k_sleep(K_MSEC(5000));
	}
}

K_THREAD_DEFINE(task_a_id, STACKSIZE, task_a, NULL, NULL, NULL, PRIORITY, K_USER, 0);
K_THREAD_DEFINE(task_b_id, STACKSIZE, task_b, NULL, NULL, NULL, PRIORITY, K_USER, 0);
