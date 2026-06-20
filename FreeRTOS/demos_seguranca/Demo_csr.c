#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

static void taskCSR( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK CSR] a tentar ler mstatus...\r\n");
        uint32_t mstatus;
        /* Em U-mode: Illegal Instruction (mcause=2) */
        /* Em M-mode: funciona normalmente */
        __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus));
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK CSR] consegui! estou em M-mode\r\n");
        vTaskDelay(3000);
    }
}

void main_blinky( void )
{
    xTaskCreate(taskCSR, "TaskCSR", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}

