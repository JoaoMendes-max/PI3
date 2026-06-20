/*
 * DEMO 3 — EXPOSIÇÃO E ESCRITA NA STACK DE OUTRA TASK (FreeRTOS)
 *
 * ATAQUE em 2 fases:
 *   Fase 1 (Exposição): A Task A guarda o endereço da sua password numa
 *   variável global leaked_addr (simulando um log de debug) e imprime-o via UART.
 *   Fase 2 (Exploração): A task adversarial lê leaked_addr e escreve directamente
 *   nesse endereço, corrompendo a password — sem endereço hardcoded.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] password em: 0x80082B9C
 *   [TASK A] password OK: 1234
 *   [TASK A] password OK: 1234
 *   [ADV] endereço lido: 0x80082B9C
 *   [ADV] a escrever na stack da Task A!
 *   [TASK A] password CORROMPIDA!
 *   ...
 *
 * PORQUÊ FUNCIONA: Tudo corre em M-mode. Não há PMP activo.
 * A adversarial lê leaked_addr (exposto pela própria Task A) e usa esse
 * endereço para escrever directamente na stack de outra task.
 *
 * Contraste com Zephyr (main_z_attack2_stack.c):
 *   Zephyr / U-mode → Store Access Fault (PMP impede a escrita)
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

/* Task A expõe aqui o endereço da sua password (ex: para fins de debug) */
volatile uint32_t leaked_addr = 0;

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
    volatile int password = 1234;

    /* Fase 1: expõe o endereço via global e via UART */
    leaked_addr = (uint32_t)&password;
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] password em: ");
    print_hex(leaked_addr);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    for(;;)
    {
        if (password == 1234)
            UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] password OK: 1234\r\n");
        else
            UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] password CORROMPIDA!\r\n");
        vTaskDelay( 1 );
    }
}

static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;

    /* Espera que a Task A exponha o endereço */
    while (leaked_addr == 0) { taskYIELD(); }

    vTaskDelay( 3 );

    /* Fase 2: usa o endereço lido da global para atacar */
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] endereco lido: ");
    print_hex(leaked_addr);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] a escrever na stack da Task A!\r\n");
    volatile int *ptr = (volatile int *)leaked_addr;
    *ptr = 0xDEAD;

    for(;;) { vTaskDelay( 10 ); }
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
