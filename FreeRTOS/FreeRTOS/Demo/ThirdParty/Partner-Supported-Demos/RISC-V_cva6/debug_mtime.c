#include <stdint.h>
#include <uart/uart.h>
extern uart_instance_t * const gp_my_uart;

static void dbg_print_hex32(uint32_t v)
{
    char buf[11];
    buf[0]='0'; buf[1]='x';
    for (int i=0;i<8;i++) {
        uint8_t nib = (v >> ((7-i)*4)) & 0xF;
        buf[2+i] = (nib < 10) ? ('0'+nib) : ('a'+nib-10);
    }
    buf[10]=0;
    UART_polled_tx_string(gp_my_uart, (uint8_t*)buf);
}

void debug_mtime_test(void)
{
    volatile uint32_t *mtime_lo    = (volatile uint32_t *)0x0200BFF8;
    volatile uint32_t *mtime_hi    = (volatile uint32_t *)0x0200BFFC;
    volatile uint32_t *mtimecmp_lo = (volatile uint32_t *)0x02004000;
    volatile uint32_t *mtimecmp_hi = (volatile uint32_t *)0x02004004;

    uint32_t t1_lo = *mtime_lo;
    uint32_t t1_hi = *mtime_hi;
    for (volatile int i = 0; i < 200000; i++);
    uint32_t t2_lo = *mtime_lo;
    uint32_t t2_hi = *mtime_hi;

    UART_polled_tx_string(gp_my_uart, (uint8_t*)"[MTIME] t1_hi=");
    dbg_print_hex32(t1_hi);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" t1_lo=");
    dbg_print_hex32(t1_lo);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"\r\n");

    UART_polled_tx_string(gp_my_uart, (uint8_t*)"[MTIME] t2_hi=");
    dbg_print_hex32(t2_hi);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" t2_lo=");
    dbg_print_hex32(t2_lo);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"\r\n");

    if (t2_lo == t1_lo && t2_hi == t1_hi) {
        UART_polled_tx_string(gp_my_uart, (uint8_t*)"[MTIME] PARADO\r\n");
    } else {
        UART_polled_tx_string(gp_my_uart, (uint8_t*)"[MTIME] a contar OK\r\n");
    }

    UART_polled_tx_string(gp_my_uart, (uint8_t*)"[MTIMECMP] hi=");
    dbg_print_hex32(*mtimecmp_hi);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" lo=");
    dbg_print_hex32(*mtimecmp_lo);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"\r\n");

    uint32_t mie_val, mstatus_val, mtvec_val;
    __asm__ volatile("csrr %0, mie"     : "=r"(mie_val));
    __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus_val));
    __asm__ volatile("csrr %0, mtvec"   : "=r"(mtvec_val));
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"[CSR] mie=");
    dbg_print_hex32(mie_val);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" mstatus=");
    dbg_print_hex32(mstatus_val);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" mtvec=");
    dbg_print_hex32(mtvec_val);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"\r\n");
}

void debug_csr_only(const char *tag)
{
    volatile uint32_t *mtimecmp_lo = (volatile uint32_t *)0x02004000;
    volatile uint32_t *mtime_lo    = (volatile uint32_t *)0x0200BFF8;
    uint32_t mie_val, mstatus_val;
    __asm__ volatile("csrr %0, mie"     : "=r"(mie_val));
    __asm__ volatile("csrr %0, mstatus" : "=r"(mstatus_val));
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"[");
    UART_polled_tx_string(gp_my_uart, (uint8_t*)tag);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"] mie=");
    dbg_print_hex32(mie_val);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" mstatus=");
    dbg_print_hex32(mstatus_val);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" mtime=");
    dbg_print_hex32(*mtime_lo);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)" mtimecmp=");
    dbg_print_hex32(*mtimecmp_lo);
    UART_polled_tx_string(gp_my_uart, (uint8_t*)"\r\n");
}
