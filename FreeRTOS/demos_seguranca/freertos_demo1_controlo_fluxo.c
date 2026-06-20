/*
 * DEMO 1 — CONTROLO DE FLUXO ADVERSARIAL (FreeRTOS)
 *
 * ATAQUE: A task adversarial modifica uma flag global e chama directamente
 * a função da Task A, alterando o fluxo de execução sem autorização.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] a correr normalmente
 *   [TASK A] a correr normalmente
 *   [TASK A] codigo executado pela ADV!     ← ataque bem-sucedido
 *   [TASK A] a correr normalmente
 *   ...
 *
 * PORQUÊ FUNCIONA: Tudo corre em M-mode. Não há isolamento entre tasks.
 * A flag global é acessível por qualquer task. A adversarial chama taskA()
 * como uma função normal — o hardware não impede nada.
 *
 * Para compilar: substituir main_blinky.c pelo conteúdo deste ficheiro,
 * ou alterar main.c para chamar main_blinky() deste ficheiro.
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

/* Flag global partilhada — qualquer task pode modificar em M-mode */
volatile int chamado_por_adversarial = 0;

static void taskA( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        if (chamado_por_adversarial)
        {
            UART_polled_tx_string(gp_my_uart,
                (uint8_t *)"[TASK A] codigo executado pela ADV!\r\n");
            return;
        }
        else
        {
            UART_polled_tx_string(gp_my_uart,
                (uint8_t *)"[TASK A] a correr normalmente\r\n");
        }
        vTaskDelay( 1 );
    }
}

static void taskAdversarial( void *pvParameters )
{
    ( void ) pvParameters;
    for(;;)
    {
        vTaskDelay( 3 );
        /* Modifica flag global e chama função de outra task directamente */
        chamado_por_adversarial = 1;
        void (*fn)(void *) = taskA;
        fn(NULL);
        chamado_por_adversarial = 0;
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
