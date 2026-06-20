/*
 * DEMO 5 — CORRUPÇÃO DO TCB (FreeRTOS)
 *
 * ATAQUE: A task adversarial obtém o handle da Task A e escreve directamente
 * no primeiro campo do TCB (o stack pointer), causando um crash no scheduler.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] a correr normalmente
 *   [TASK C] a correr normalmente
 *   [ADV] TCB da Task A em: 0x8008XXXX
 *   [ADV] a corromper stack pointer da Task A!
 *   [ADV] stack pointer corrompido!
 *   [crash / comportamento indefinido — o scheduler usa um SP inválido]
 *
 * PORQUÊ FUNCIONA: O TCB é uma struct em RAM. Em M-mode não há protecção
 * de memória. Qualquer task com o handle pode escrever nos campos internos
 * do TCB directamente por cast de ponteiro.
 *
 * Contraste com Zephyr (main_z_attack4_tcb.c):
 *   Zephyr / U-mode → Store Access Fault (PMP impede escrita no struct k_thread)
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

TaskHandle_t handleTaskA;

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

static void taskA( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] a correr normalmente\r\n");
        vTaskDelay( 1 );
    }
}

static void taskC( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK C] a correr normalmente\r\n");
        vTaskDelay( 1 );
    }
}

static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;
    vTaskDelay( 5 );

    uint32_t *tcb = (uint32_t *)handleTaskA;

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] TCB da Task A em: ");
    print_hex((uint32_t)handleTaskA);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] a corromper stack pointer da Task A!\r\n");
    tcb[0] = 0xDEADBEEF;
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] stack pointer corrompido!\r\n");

    for(;;) { vTaskDelay( 10 ); }
}

void main_blinky( void )
{
    xTaskCreate(taskA, "TaskA", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, &handleTaskA);
    xTaskCreate(taskC, "TaskC", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(taskAdversarial, "Adv", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}
