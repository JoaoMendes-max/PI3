#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

/* ── Hardware ─────────────────────────────────────── */
#define GPIO_BASE_ADDR  0x40000000

typedef struct {
    volatile uint32_t GPIO_DATA;
    volatile uint32_t GPIO_TRI;
    volatile uint32_t GPIO2_DATA;
    volatile uint32_t GPIO2_TRI;
} AXI_GPIO_t;

#define GPIO ((AXI_GPIO_t *) GPIO_BASE_ADDR)

/* Canal 1 (8 bits):
 * bit 7 = JD7 | bit 6 = JD4 | bit 5 = JD3 | bit 4 = JD2
 * bit 3 = JD1 | bit 2 = LD2 | bit 1 = LD1 | bit 0 = LD0
 * IN1 -> JD1 (bit 3) | IN2 -> JD2 (bit 4)
 */
#define PIN_IN1  (1 << 3)   /* JD1 */
#define PIN_IN2  (1 << 4)   /* JD2 */

#define MOTOR_FWD  (PIN_IN1)   /* IN1=1, IN2=0 → frente */
#define MOTOR_OFF  (0)         /* IN1=0, IN2=0 → parado */

#define PWM_PERIOD_MS  10

/* Canal 2 (8 bits) - input:
 * bit 7 = SW3 | bit 6 = SW2 | bit 5 = SW1 | bit 4 = SW0
 * bit 3 = BTND | bit 2 = BTNU | bit 1 = BTNR | bit 0 = BTNL
 */
#define SW0  (1 << 4)

/* ── Shared ───────────────────────────────────────── */
static volatile uint32_t leaked_addr = 0;
static volatile int addr_ready = 0;

static void print_hex(uint32_t val)
{
    char buf[11];
    buf[0] = '0'; buf[1] = 'x';
    for (int i = 9; i >= 2; i--) {
        int nibble = val & 0xF;
        buf[i] = nibble < 10 ? '0' + nibble : 'A' + nibble - 10;
        val >>= 4;
    }
    buf[10] = '\0';
    UART_polled_tx_string(gp_my_uart, (uint8_t *)buf);
}

/* ── Task Motor ───────────────────────────────────── */
static void taskMotor( void *pvParameters )
{
    ( void ) pvParameters;

    volatile uint32_t pwm_duty = 70;

    leaked_addr = (uint32_t)&pwm_duty;
    addr_ready = 1;

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[MOTOR] pwm_duty em: ");
    print_hex((uint32_t)&pwm_duty);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    GPIO->GPIO_TRI = 0x00;  /* canal 1 todo output */

    for(;;)
    {
        uint32_t on_ms  = (pwm_duty * PWM_PERIOD_MS) / 100;
        uint32_t off_ms = PWM_PERIOD_MS - on_ms;

        GPIO->GPIO_DATA = MOTOR_FWD;
        vTaskDelay(pdMS_TO_TICKS(on_ms));

        GPIO->GPIO_DATA = MOTOR_OFF;
        vTaskDelay(pdMS_TO_TICKS(off_ms));

        if (pwm_duty == 30)
            UART_polled_tx_string(gp_my_uart, (uint8_t *)"[MOTOR] pwm_duty CORROMPIDO — motor a abrandar!\r\n");
    }
}

/* ── Task Adversarial ─────────────────────────────── */
static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;

    while (addr_ready == 0) {
        vTaskDelay(1);
    }

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] a aguardar SW0...\r\n");

    /* espera SW0 */
    while (!(GPIO->GPIO2_DATA & SW0)) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] SW0 ativo! endereco lido: ");
    print_hex(leaked_addr);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    volatile uint32_t *ptr = (volatile uint32_t *)leaked_addr;

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] a corromper pwm_duty...\r\n");
    *ptr = 30;  /* sem PMP → motor abranda de 70% para 30% */
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] pwm_duty corrompido — motor a abrandar!\r\n");

    for(;;) { vTaskDelay(10); }
}

/* ── Main ─────────────────────────────────────────── */
void main_blinky( void )
{
    xTaskCreate(taskMotor, "Motor", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(taskAdversarial, "Adv", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}