#include "FreeRTOS.h"
#include "task.h"
#include <uart/uart.h>

extern uart_instance_t * const gp_my_uart;

static void taskA( void *pvParameters )
{
	uint32_t mstatus;
	__asm__ volatile("csrr %0, mstatus" : "=r"(mstatus));
	UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] mstatus lido\r\n");

	( void ) pvParameters;
	for( ;; )
	{
		UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] a correr\r\n");
		vTaskDelay( pdMS_TO_TICKS( 500 ) );
	}
}

static void taskB( void *pvParameters )
{
	( void ) pvParameters;
	for( ;; )
	{
		UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK B] a correr\r\n");
		vTaskDelay( pdMS_TO_TICKS( 1500 ) );
	}
}

void main_blinky( void )
{
	xTaskCreate( taskA, "TaskA", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL );
	xTaskCreate( taskB, "TaskB", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL );
	vTaskStartScheduler();
	for( ;; );
}
