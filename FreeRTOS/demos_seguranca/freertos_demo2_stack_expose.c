/*
 * DEMO 2 — EXPOSIÇÃO DE ENDEREÇO DE STACK (FreeRTOS)
 *
 * ATAQUE: A Task A imprime o endereço de uma variável local sensível
 * (password na stack). Em FreeRTOS / M-mode, qualquer task pode ler
 * esse endereço e aceder directamente à memória.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] password em: 0x80082B9C
 *   [TASK A] a correr normalmente
 *   [ADV]    a correr (podia usar o endereço impresso para atacar)
 *   [TASK A] a correr normalmente
 *   ...
 *
 * PORQUÊ É PERIGOSO: Em M-mode não há nenhuma protecção de memória.
 * A task adversarial podia guardar o endereço impresso e escrever lá
 * (ver Demo 3 para a exploração concreta).
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

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
    int password = 1234;

    /* Expõe o endereço da variável sensível */
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] password em: ");
    print_hex((uint32_t)&password);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    for(;;)
    {
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] a correr normalmente\r\n");
        vTaskDelay( 1 );
    }
}

static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        vTaskDelay( 3 );
        /* Em M-mode podia usar o endereço impresso para atacar directamente */
        UART_polled_tx_string(gp_my_uart,
            (uint8_t *)"[ADV] a correr (endereço da Task A visível no output)\r\n");
    }
}

void main_blinky( void )
{
    xTaskCreate(taskA, "TaskA", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(taskAdversarial, "Adv", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}
