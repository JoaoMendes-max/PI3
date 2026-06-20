//
// Created by mendes on 11/06/26.
//

#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/app_memory/app_memdomain.h>
#include <zephyr/sys/libc-hooks.h>

/* ── Hardware ─────────────────────────────────────── */
#define GPIO_BASE_ADDR  0x40000000

typedef struct {
    volatile uint32_t GPIO_DATA;
    volatile uint32_t GPIO_TRI;
    volatile uint32_t GPIO2_DATA;
    volatile uint32_t GPIO2_TRI;
} AXI_GPIO_t;

#define GPIO ((AXI_GPIO_t *) GPIO_BASE_ADDR)


#define PIN_IN1  (1 << 3)   /* JD1 */
#define PIN_IN2  (1 << 4)   /* JD2 */

#define MOTOR_FWD  (PIN_IN1)   /* IN1=1, IN2=0 → frente */
#define MOTOR_OFF  (0)         /* IN1=0, IN2=0 → parado */

#define PWM_PERIOD_MS  10


#define SW0  (1 << 4)

/* ── Shared Memory ────────────────────────────────── */
#define STACKSIZE 2048
#define PRIORITY  7

K_APPMEM_PARTITION_DEFINE(shared_part);

K_APP_DMEM(shared_part) volatile uint32_t leaked_addr = 0;
K_APP_DMEM(shared_part) volatile uint32_t shared_ready = 0;

/* ── Memory Domains ───────────────────────────────── */
K_MEM_PARTITION_DEFINE(gpio_partition,
    GPIO_BASE_ADDR,
    0x1000,
    K_MEM_PARTITION_P_RW_U_RW);

static struct k_mem_domain domMotor;
static struct k_mem_domain domAdv;

/* ── Thread objects ───────────────────────────────── */
struct k_thread task_motor_thread;
K_THREAD_STACK_DEFINE(task_motor_stack, STACKSIZE);

struct k_thread task_adv_thread;
K_THREAD_STACK_DEFINE(task_adv_stack, STACKSIZE);

/* ── Task Motor ───────────────────────────────────── */
void task_motor_entry(void *p1, void *p2, void *p3)
{
    printk("[MOTOR] a correr\n");

    volatile uint32_t pwm_duty = 70;

    leaked_addr = (uint32_t)&pwm_duty;
    shared_ready = 1;
    printk("[MOTOR] pwm_duty em stack: 0x%08x\n", (uint32_t)&pwm_duty);

    GPIO->GPIO_TRI = 0x00;  /* canal 1 todo output */

    while (1) {
        uint32_t on_ms  = (pwm_duty * PWM_PERIOD_MS) / 100;
        uint32_t off_ms = PWM_PERIOD_MS - on_ms;

        GPIO->GPIO_DATA = MOTOR_FWD;
        if (on_ms > 0)  k_sleep(K_MSEC(on_ms));

        GPIO->GPIO_DATA = MOTOR_OFF;
        if (off_ms > 0) k_sleep(K_MSEC(off_ms));

        if (pwm_duty == 30)
            printk("[MOTOR] pwm_duty CORROMPIDO — motor a abrandar!\n");
    }
}

/* ── Task Adversarial ─────────────────────────────── */
void task_adv_entry(void *p1, void *p2, void *p3)
{
    printk("[ADV] a aguardar SW0...\n");

    while (shared_ready == 0) {
        k_sleep(K_MSEC(100));
    }

    /* espera SW0 */
    while (!(GPIO->GPIO2_DATA & SW0)) {
        k_sleep(K_MSEC(100));
    }

    volatile uint32_t *ptr = (volatile uint32_t *)leaked_addr;

    printk("[ADV] SW0 ativo! endereco lido: 0x%08x\n", (uint32_t)ptr);
    printk("[ADV] a tentar corromper pwm_duty...\n");

    *ptr = 30;  /* Zephyr → Store Access Fault | FreeRTOS → motor abranda */

    printk("[ADV] pwm_duty corrompido — motor a abrandar!\n");  /* nunca executa no Zephyr */
}

/* ── Main ─────────────────────────────────────────── */
int main(void)
{
    k_tid_t tMotor, tAdv;

    printk("[MAIN] a configurar dominios...\n");

    tMotor = k_thread_create(&task_motor_thread, task_motor_stack, STACKSIZE,
                             task_motor_entry, NULL, NULL, NULL,
                             PRIORITY, K_USER, K_FOREVER);

    tAdv = k_thread_create(&task_adv_thread, task_adv_stack, STACKSIZE,
                           task_adv_entry, NULL, NULL, NULL,
                           PRIORITY, K_USER, K_FOREVER);

    struct k_mem_partition *parts_motor[] = {
#if Z_LIBC_PARTITION_EXISTS
        &z_libc_partition,
#endif
        &shared_part,
        &gpio_partition
    };

    struct k_mem_partition *parts_adv[] = {
#if Z_LIBC_PARTITION_EXISTS
        &z_libc_partition,
#endif
        &shared_part,
        &gpio_partition
    };

    k_mem_domain_init(&domMotor, ARRAY_SIZE(parts_motor), parts_motor);
    k_mem_domain_add_thread(&domMotor, tMotor);
    printk("[MAIN] domMotor configurado\n");

    k_mem_domain_init(&domAdv, ARRAY_SIZE(parts_adv), parts_adv);
    k_mem_domain_add_thread(&domAdv, tAdv);
    printk("[MAIN] domAdv configurado\n");

    k_thread_start(tMotor);
    k_thread_start(tAdv);

    printk("[MAIN] threads arrancadas\n");
    return 0;
}