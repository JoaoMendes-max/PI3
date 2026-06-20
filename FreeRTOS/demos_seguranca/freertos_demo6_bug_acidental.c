/*
 * DEMO 6 — OVERFLOW LOCAL OBSERVAVEL (FreeRTOS)
 *
 * CENARIO: Task A tem um array local na sua stack. Task Buggy tambem tem
 * um array local na sua stack. Task A publica o endereco do seu array
 * (simulando um leak/log de debug) e Task Buggy usa um indice fora dos
 * limites do seu proprio array local ate atingir o array local da Task A.
 *
 * O objectivo e tornar visivel que "local" nao significa "protegido":
 * em FreeRTOS / M-mode, uma task pode escrever fora da sua stack e alterar
 * dados locais de outra task sem qualquer fault de hardware.
 *
 * RESULTADO ESPERADO (FreeRTOS / M-mode):
 *   [TASK A] dados_task_a local @ 0x80082Bxx = [0x0000000A, ...] OK
 *   [BUG]    buffer_buggy local @ 0x80082Cxx = [0x00000001, ...]
 *   [BUG]    escrita fora dos limites concluida
 *   [TASK A] dados_task_a local @ 0x80082Bxx = [0xBEEF0000, ...] CORROMPIDOS
 *   ...
 *
 * PORQUÊ ACONTECE: Em M-mode não há PMP activo entre tasks.
 * O overflow escreve para além de buffer_buggy, quSe e local da Task Buggy,
 * e atinge dados_task_a, que e local da Task A. FreeRTOS nao detecta nem
 * reporta nada — a corrupcao e silenciosa.
 *
 * Contraste com Zephyr (main_z_bug_acidental.c):
 *   Zephyr / U-mode → Store Access Fault contém o bug na Task Buggy.
 *   Task A não é afectada e continua a correr normalmente.
 */

#include <stdint.h>
#include "FreeRTOS.h"
#include "task.h"
#include "uart/uart.h"

extern uart_instance_t * const gp_my_uart;

/* Apenas metadados de coordenacao. Os arrays demonstrados sao locais. */
volatile uint32_t leaked_dados_task_a_addr = 0;

static void print_hex32(uint32_t val)
{
    char buf[11];
    buf[0] = '0';
    buf[1] = 'x';
    for (int i = 9; i >= 2; i--) {
        int nibble = val & 0xF;
        buf[i] = (nibble < 10) ? ('0' + nibble) : ('A' + nibble - 10);
        val >>= 4;
    }
    buf[10] = '\0';
    UART_polled_tx_string(gp_my_uart, (uint8_t *)buf);
}

static void print_array4(const char *prefix, volatile int *array)
{
    UART_polled_tx_string(gp_my_uart, (uint8_t *)prefix);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)" @ ");
    print_hex32((uint32_t)array);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)" = [");
    print_hex32((uint32_t)array[0]);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)", ");
    print_hex32((uint32_t)array[1]);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)", ");
    print_hex32((uint32_t)array[2]);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)", ");
    print_hex32((uint32_t)array[3]);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"]");
}

static void taskA( void *pvParameters )
{
    ( void ) pvParameters;

    volatile int dados_task_a[4] = { 10, 20, 30, 40 };

    leaked_dados_task_a_addr = (uint32_t)&dados_task_a[0];

    for(;;)
    {
        print_array4("[TASK A] dados_task_a local", dados_task_a);

        if (dados_task_a[0] == 10 && dados_task_a[1] == 20 &&
            dados_task_a[2] == 30 && dados_task_a[3] == 40)
            UART_polled_tx_string(gp_my_uart, (uint8_t *)" OK\r\n");
        else
            UART_polled_tx_string(gp_my_uart, (uint8_t *)" CORROMPIDOS!\r\n");

        vTaskDelay( 1 );
    }
}

static void taskBuggy( void *pvParameters )
{
    ( void ) pvParameters;
    volatile int buffer_buggy[4] = { 1, 2, 3, 4 };

    while (leaked_dados_task_a_addr == 0) {
        taskYIELD();
    }

    vTaskDelay( 3 );

    print_array4("[BUG]    buffer_buggy local antes", buffer_buggy);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");
    print_array4("[BUG]    dados_task_a visto antes",
                 (volatile int *)leaked_dados_task_a_addr);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    uint32_t buffer_addr = (uint32_t)&buffer_buggy[0];
    uint32_t target_addr = leaked_dados_task_a_addr;
    int32_t byte_delta = (int32_t)(target_addr - buffer_addr);
    int32_t index_delta = byte_delta / (int32_t)sizeof(buffer_buggy[0]);

    UART_polled_tx_string(gp_my_uart,
        (uint8_t *)"[BUG]    indice fora dos limites ate dados_task_a: ");
    print_hex32((uint32_t)index_delta);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    /* BUG: escrita fora dos limites de buffer_buggy. O indice pode ser
     * negativo ou muito maior que 3, dependendo do layout das stacks. */
    for (int i = 0; i < 4; i++) {
        buffer_buggy[index_delta + i] = (int)(0xBEEF0000u + (uint32_t)i);
    }

    UART_polled_tx_string(gp_my_uart,
        (uint8_t *)"[BUG]    escrita fora dos limites concluida\r\n");
    print_array4("[BUG]    buffer_buggy local depois", buffer_buggy);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");
    print_array4("[BUG]    dados_task_a visto depois",
                 (volatile int *)leaked_dados_task_a_addr);
    UART_polled_tx_string(gp_my_uart, (uint8_t *)"\r\n");

    for(;;) { vTaskDelay( 10 ); }
}

void main_blinky( void )
{
    xTaskCreate(taskA,     "TaskA", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    xTaskCreate(taskBuggy, "Buggy", configMINIMAL_STACK_SIZE * 2U,
                NULL, tskIDLE_PRIORITY + 1, NULL);
    vTaskStartScheduler();
    for(;;);
}
