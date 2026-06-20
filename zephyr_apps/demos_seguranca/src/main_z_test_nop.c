#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>

#define STACKSIZE 2048
#define PRIORITY  7

void task_test_entry(void *p1, void *p2, void *p3)
{
    k_sleep(K_MSEC(2000));
    printk("[TEST] sw com 2 NOPs antes + segundo sw a seguir\n");
    printk("[TEST] sem RAW hazard, scoreboard quase vazio\n");

    /*
     * lui  t1      <- carrega endereco
     * nop          <- quebra RAW: t1 disponivel antes do sw chegar ao EX
     * nop          <- idem
     * sw zero,0(t1) <- store que falha (mepc aqui)
     * sw zero,0(t1) <- segundo store imediatamente a seguir
     *
     * Theory 1 (scoreboard): mcause=7, segundo sw chega à store_unit em N+1
     * Theory 2 (RAW hazard): mcause=5, sem RAW -> st_ready=1 -> VALID_STORE -> req=0
     */
    __asm__ volatile(
        "lui  t1, 0x80011\n"
        "nop\n"
        "nop\n"
        "sw   zero, 0(t1)\n"
        "sw   zero, 0(t1)\n"
        ::: "t1"
    );

    printk("[TEST] sem fault -- nao devia chegar aqui\n");
}

K_THREAD_DEFINE(task_test_id, STACKSIZE, task_test_entry,
                NULL, NULL, NULL, PRIORITY, K_USER, 0);
