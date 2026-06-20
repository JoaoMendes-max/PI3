/*
 * DEMO 4 — CORRUPÇÃO DE VARIÁVEL GLOBAL (FreeRTOS)
 *
 * ATAQUE: A task adversarial escreve directamente na variável global
 * da Task A, corrompendo os dados que ela usa.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] dados = 42 (OK)
 *   [TASK A] dados = 42 (OK)
 *   [ADV] a corromper dados da Task A...
 *   [TASK A] dados CORROMPIDOS!
 *   [TASK A] dados CORROMPIDOS!
 *   ...
 *
 * PORQUÊ FUNCIONA: Tudo corre em M-mode. Variáveis globais são acessíveis
 * por todas as tasks sem restrição. A adversarial escreve em dados_task_a
 * como se fosse a sua própria variável.
 *
 * Contraste com Zephyr (main_z_attack3_global.c):
 *   Zephyr / U-mode → Store Access Fault (PMP impede a escrita)
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

/* Variavel global */
volatile int dados_task_a = 42;

/* Task A — imprime o valor da sua variável */
static void taskA( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        if (dados_task_a == 42)
            UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] dados = 42 (OK)\r\n");
        else
            UART_polled_tx_string(gp_my_uart, (uint8_t *)"[TASK A] dados CORROMPIDOS!\r\n");
        vTaskDelay( 1 );
    }
}

/* Task Adversarial — corrompe a variável global usada na task A */
static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        vTaskDelay( 3 );
        UART_polled_tx_string(gp_my_uart, (uint8_t *)"[ADV] a corromper dados da Task A...\r\n");
        dados_task_a = 0xDEAD;
    }
}

void main_blinky( void )
{
    xTaskCreate(taskA, "TaskA", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(taskAdversarial, "Adv", configMINIMAL_STACK_SIZE * 2U, NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}
