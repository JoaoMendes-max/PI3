#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include <uart/uart.h>

extern uart_instance_t * const gp_my_uart;

static QueueHandle_t xQueue;

static void print_hex(uint32_t val)
{
    char buf[11];
    const char *hex = "0123456789abcdef";
    buf[0] = '0'; buf[1] = 'x';
    for(int i = 0; i < 8; i++)
        buf[2+i] = hex[(val >> (28 - 4*i)) & 0xF];
    buf[10] = '\0';
    UART_polled_tx_string(gp_my_uart, (uint8_t *)buf);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");
}

static void taskProdutora( void *pvParameters )
{
    uint32_t valor = 0;
    ( void ) pvParameters;
    for( ;; )
    {
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[PROD] a enviar: ");
        print_hex(valor);
        xQueueSend(xQueue, &valor, portMAX_DELAY);
        valor++;
        taskYIELD();
    }
}

static void taskConsumidora( void *pvParameters )
{
    uint32_t valor;
    ( void ) pvParameters;
    for( ;; )
    {
        xQueueReceive(xQueue, &valor, portMAX_DELAY);
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[CONS] recebeu: ");
        print_hex(valor);
    }
}

void main_blinky( void )
{
    xQueue = xQueueCreate(5, sizeof(uint32_t));
    xTaskCreate( taskProdutora,  "Prod", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL );
    xTaskCreate( taskConsumidora, "Cons", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL );
    vTaskStartScheduler();
    for( ;; );
}
