/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PCC_REG_H
#define PCC_REG_H
#include <stdint.h>

/* ================================================================================ */
/* ================                PCC Register               ================ */
/* ===========     Reference: RTL87x2G_PERI-ON_20221201_v1.xlsx     =========== */
/* ================================================================================ */
typedef struct
{
    /* 0x300        0x4000_2300
        3:0     R/W    r_spic0_div_sel                 4'h0
        4       R/W    r_spic0_div_en                  1'h0
        5       R/W    r_spic0_clk_src_en              1'h1
        6       R/W    RSVD                            1'h0
        7       R/W    RSVD                            1'h0
        8       R/W    r_spic0_mux_1_clk_cg_en         1'h1
        9       R/W    r_spic0_clk_src_sel0            1'h0
        10      R/W    r_spic0_clk_src_sel1            1'h0
        11      R/W    RSVD                            1'h0
        15:12   R/W    RSVD                            4'h0
        17:16   R/W    r_flash0_phy_clk_sel            2'h0
        18      R/W    r_flash0_clk_inv_en             1'b0
        26:19   R/W    r_pon_dlysel_spic0              8'h0
        27      R/W    spic0_phy_func_en               1'h0
        28      R/W    spic0_phy_str_en                1'h1
        29      R/W    RSVD                            1'h0
        30      R/W    spic0_ck_en                     1'h0
        31      R/W    spic0_func_en                   1'h0
    */
    union
    {
        __IO uint32_t REG_PERI_SPIC0_CTL;
        struct
        {
            __IO uint32_t r_spic0_div_sel: 4;
            __IO uint32_t r_spic0_div_en: 1;
            __IO uint32_t r_spic0_clk_src_en: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t r_spic0_mux_1_clk_cg_en: 1;
            __IO uint32_t r_spic0_clk_src_sel0: 1;
            __IO uint32_t r_spic0_clk_src_sel1: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 4;
            __IO uint32_t r_flash0_phy_clk_sel: 2;
            __IO uint32_t r_flash0_clk_inv_en: 1;
            __IO uint32_t r_pon_dlysel_spic0: 8;
            __IO uint32_t spic0_phy_func_en: 1;
            __IO uint32_t spic0_phy_str_en: 1;
            __IO uint32_t RESERVED_0: 1;
            __IO uint32_t spic0_ck_en: 1;
            __IO uint32_t spic0_func_en: 1;
        } BITS_300;
    } u_300;

    /* 0x304        0x4000_2304
        3:0     R/W    r_spic1_div_sel                 4'h0
        4       R/W    r_spic1_div_en                  1'h0
        5       R/W    r_spic1_clk_src_en              1'h1
        6       R/W    RSVD                            1'h0
        7       R/W    RSVD                            1'h0
        8       R/W    r_spic1_mux_1_clk_cg_en         1'h0
        9       R/W    r_spic1_clk_src_sel0            1'h0
        10      R/W    r_spic1_clk_src_sel1            1'h0
        11      R/W    RSVD                            1'h0
        15:12   R/W    RSVD                            4'h0
        17:16   R/W    r_spic1_phy_clk_sel             2'h0
        18      R/W    r_spic1_clk_inv_en              1'b0
        26:19   R/W    r_pon_dlysel_spic1              8'h0
        27      R/W    spic1_phy_func_en               1'h0
        28      R/W    spic1_phy_str_en                1'h0
        29      R/W    spic1_phy_apb_ck_en             1'h0
        30      R/W    spic1_ck_en                     1'h0
        31      R/W    spic1_func_en                   1'h0
    */
    union
    {
        __IO uint32_t REG_PERI_SPIC1_CTL;
        struct
        {
            __IO uint32_t r_spic1_div_sel: 4;
            __IO uint32_t r_spic1_div_en: 1;
            __IO uint32_t r_spic1_clk_src_en: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t r_spic1_mux_1_clk_cg_en: 1;
            __IO uint32_t r_spic1_clk_src_sel0: 1;
            __IO uint32_t r_spic1_clk_src_sel1: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t RESERVED_0: 4;
            __IO uint32_t r_spic1_phy_clk_sel: 2;
            __IO uint32_t r_spic1_clk_inv_en: 1;
            __IO uint32_t r_pon_dlysel_spic1: 8;
            __IO uint32_t spic1_phy_func_en: 1;
            __IO uint32_t spic1_phy_str_en: 1;
            __IO uint32_t spic1_phy_apb_ck_en: 1;
            __IO uint32_t spic1_ck_en: 1;
            __IO uint32_t spic1_func_en: 1;
        } BITS_304;
    } u_304;

    /* 0x308        0x4000_2308
        3:0     R/W    r_spic2_div_sel                 4'h0
        4       R/W    r_spic2_div_en                  1'h0
        5       R/W    r_spic2_clk_src_en              1'h1
        6       R/W    RSVD                            1'h0
        7       R/W    RSVD                            1'h0
        8       R/W    r_spic2_mux_1_clk_cg_en         1'h0
        9       R/W    r_spic2_clk_src_sel0            1'h0
        10      R/W    r_spic2_clk_src_sel1            1'h0
        11      R/W    RSVD                            1'h0
        15:12   R/W    RSVD                            4'h0
        17:16   R/W    r_spic2_phy_clk_sel             2'h0
        18      R/W    r_spic2_clk_inv_en              1'b0
        26:19   R/W    r_pon_dlysel_spic2              8'h0
        27      R/W    spic2_phy_func_en               1'h0
        28      R/W    spic2_phy_str_en                1'h0
        29      R/W    RSVD                            1'h0
        30      R/W    spic2_ck_en                     1'h0
        31      R/W    spic2_func_en                   1'h0
    */
    union
    {
        __IO uint32_t REG_PERI_SPIC2_CTL;
        struct
        {
            __IO uint32_t r_spic2_div_sel: 4;
            __IO uint32_t r_spic2_div_en: 1;
            __IO uint32_t r_spic2_clk_src_en: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t r_spic2_mux_1_clk_cg_en: 1;
            __IO uint32_t r_spic2_clk_src_sel0: 1;
            __IO uint32_t r_spic2_clk_src_sel1: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 4;
            __IO uint32_t r_spic2_phy_clk_sel: 2;
            __IO uint32_t r_spic2_clk_inv_en: 1;
            __IO uint32_t r_pon_dlysel_spic2: 8;
            __IO uint32_t spic2_phy_func_en: 1;
            __IO uint32_t spic2_phy_str_en: 1;
            __IO uint32_t RESERVED_0: 1;
            __IO uint32_t spic2_ck_en: 1;
            __IO uint32_t spic2_func_en: 1;
        } BITS_308;
    } u_308;

    /* 0x30C        0x4000_230c
        0       R/W    gdma0_func_en                   1'h0
        1       R/W    gdma0_ck_en                     1'h0
        31:2    R/W    RSVD                            30'h0
    */
    union
    {
        __IO uint32_t REG_DMA_CTRL0;
        struct
        {
            __IO uint32_t gdma0_func_en: 1;
            __IO uint32_t gdma0_ck_en: 1;
            __IO uint32_t RESERVED_0: 30;
        } BITS_30C;
    } u_30C;

    /* 0x310        0x4000_2310
        0       R/W    spi0_func_en                    1'h0
        1       R/W    spi0_ck_en                      1'h0
        2       R/W    spi0_div_en                     1'h0
        5:3     R/W    spi0_div_sel                    3'b000
        6       R/W    spi0_brg_en                     1'h0
        7       R/W    spi0_hs_ck_en                   1'h0
        8       R/W    spi1_func_en                    1'h0
        9       R/W    spi1_ck_en                      1'h0
        10      R/W    spi1_div_en                     1'h0
        13:11   R/W    spi1_div_sel                    3'b000
        14      R/W    spi1_brg_en                     1'h0
        15      R/W    PON_SPI0_MST                    1'h0
        16      R/W    spi0_s_func_en                  1'h0
        17      R/W    spi0_s_ck_en                    1'h0
        18      R/W    spi0_s_div_en                   1'h0
        21:19   R/W    spi0_s_div_sel                  3'b000
        22      R/W    RSVD                            1'h0
        23      R/W    RSVD                            1'h0
        24      R/W    spi0_src_clk_sel0               1'h0
        25      R/W    spi0_src_clk_sel1               1'h0
        26      R/W    spi0_s_src_clk_sel0             1'h0
        27      R/W    spi0_s_src_clk_sel1             1'h0
        28      R/W    spi0_mux_clk_cg_en              1'h0
        29      R/W    spi0_s_mux_clk_cg_en            1'h0
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_SPI_PERI_CTL0;
        struct
        {
            __IO uint32_t spi0_func_en: 1;
            __IO uint32_t spi0_ck_en: 1;
            __IO uint32_t spi0_div_en: 1;
            __IO uint32_t spi0_div_sel: 3;
            __IO uint32_t spi0_brg_en: 1;
            __IO uint32_t spi0_hs_ck_en: 1;
            __IO uint32_t spi1_func_en: 1;
            __IO uint32_t spi1_ck_en: 1;
            __IO uint32_t spi1_div_en: 1;
            __IO uint32_t spi1_div_sel: 3;
            __IO uint32_t spi1_brg_en: 1;
            __IO uint32_t PON_SPI0_MST: 1;
            __IO uint32_t spi0_s_func_en: 1;
            __IO uint32_t spi0_s_ck_en: 1;
            __IO uint32_t spi0_s_div_en: 1;
            __IO uint32_t spi0_s_div_sel: 3;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t spi0_src_clk_sel0: 1;
            __IO uint32_t spi0_src_clk_sel1: 1;
            __IO uint32_t spi0_s_src_clk_sel0: 1;
            __IO uint32_t spi0_s_src_clk_sel1: 1;
            __IO uint32_t spi0_mux_clk_cg_en: 1;
            __IO uint32_t spi0_s_mux_clk_cg_en: 1;
            __IO uint32_t RESERVED_0: 2;
        } BITS_310;
    } u_310;

    /* 0x314        0x4000_2314
        0       R/W    i2c0_func_en                    1'h0
        1       R/W    i2c0_ck_en                      1'h0
        2       R/W    i2c0_div_en                     1'h0
        5:3     R/W    i2c0_div_sel                    3'b000
        7:6     R/W    RSVD                            2'h0
        8       R/W    i2c1_func_en                    1'h0
        9       R/W    i2c1_ck_en                      1'h0
        10      R/W    i2c1_div_en                     1'h0
        13:11   R/W    i2c1_div_sel                    3'b000
        15:14   R/W    RSVD                            2'h0
        16      R/W    i2c2_func_en                    1'h0
        17      R/W    i2c2_ck_en                      1'h0
        18      R/W    i2c2_div_en                     1'h0
        21:19   R/W    i2c2_div_sel                    3'b000
        23:22   R/W    RSVD                            2'h0
        24      R/W    i2c3_func_en                    1'h0
        25      R/W    i2c3_ck_en                      1'h0
        26      R/W    i2c3_div_en                     1'h0
        29:27   R/W    i2c3_div_sel                    3'b000
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_I2C_PERI_CTL0;
        struct
        {
            __IO uint32_t i2c0_func_en: 1;
            __IO uint32_t i2c0_ck_en: 1;
            __IO uint32_t i2c0_div_en: 1;
            __IO uint32_t i2c0_div_sel: 3;
            __IO uint32_t RESERVED_3: 2;
            __IO uint32_t i2c1_func_en: 1;
            __IO uint32_t i2c1_ck_en: 1;
            __IO uint32_t i2c1_div_en: 1;
            __IO uint32_t i2c1_div_sel: 3;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t i2c2_func_en: 1;
            __IO uint32_t i2c2_ck_en: 1;
            __IO uint32_t i2c2_div_en: 1;
            __IO uint32_t i2c2_div_sel: 3;
            __IO uint32_t RESERVED_1: 2;
            __IO uint32_t i2c3_func_en: 1;
            __IO uint32_t i2c3_ck_en: 1;
            __IO uint32_t i2c3_div_en: 1;
            __IO uint32_t i2c3_div_sel: 3;
            __IO uint32_t RESERVED_0: 2;
        } BITS_314;
    } u_314;

    /* 0x318        0x4000_2318
        0       R/W    r_PMUX_1_WIRE_UART0_EN          1'h0
        1       R/W    rtk_uart0_func_en               1'h0
        2       R/W    rtk_uart0_ck_en                 1'h0
        3       R/W    rtk_uart0_div_en                1'h0
        6:4     R/W    rtk_uart0_div_sel               3'b000
        7       R/W    RSVD                            1'h0
        8       R/W    r_PMUX_1_WIRE_UART1_EN          1'h0
        9       R/W    rtk_uart1_func_en               1'h0
        10      R/W    rtk_uart1_ck_en                 1'h0
        11      R/W    rtk_uart1_div_en                1'h0
        14:12   R/W    rtk_uart1_div_sel               3'b000
        15      R/W    RSVD                            1'h0
        16      R/W    r_PMUX_1_WIRE_UART2_EN          1'h0
        17      R/W    rtk_uart2_func_en               1'h0
        18      R/W    rtk_uart2_ck_en                 1'h0
        19      R/W    rtk_uart2_div_en                1'h0
        22:20   R/W    rtk_uart2_div_sel               3'b000
        23      R/W    RSVD                            1'h0
        24      R/W    r_PMUX_1_WIRE_UART3_EN          1'h0
        25      R/W    rtk_uart3_func_en               1'h0
        26      R/W    rtk_uart3_ck_en                 1'h0
        27      R/W    rtk_uart3_div_en                1'h0
        30:28   R/W    rtk_uart3_div_sel               3'b000
        31      R/W    RSVD                            1'h0
    */
    union
    {
        __IO uint32_t REG_UART_PERI_CTL0;
        struct
        {
            __IO uint32_t r_PMUX_1_WIRE_UART0_EN: 1;
            __IO uint32_t rtk_uart0_func_en: 1;
            __IO uint32_t rtk_uart0_ck_en: 1;
            __IO uint32_t rtk_uart0_div_en: 1;
            __IO uint32_t rtk_uart0_div_sel: 3;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t r_PMUX_1_WIRE_UART1_EN: 1;
            __IO uint32_t rtk_uart1_func_en: 1;
            __IO uint32_t rtk_uart1_ck_en: 1;
            __IO uint32_t rtk_uart1_div_en: 1;
            __IO uint32_t rtk_uart1_div_sel: 3;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t r_PMUX_1_WIRE_UART2_EN: 1;
            __IO uint32_t rtk_uart2_func_en: 1;
            __IO uint32_t rtk_uart2_ck_en: 1;
            __IO uint32_t rtk_uart2_div_en: 1;
            __IO uint32_t rtk_uart2_div_sel: 3;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t r_PMUX_1_WIRE_UART3_EN: 1;
            __IO uint32_t rtk_uart3_func_en: 1;
            __IO uint32_t rtk_uart3_ck_en: 1;
            __IO uint32_t rtk_uart3_div_en: 1;
            __IO uint32_t rtk_uart3_div_sel: 3;
            __IO uint32_t RESERVED_0: 1;
        } BITS_318;
    } u_318;

    /* 0x31C        0x4000_231c
        0       R/W    auxadc_func_en                  1'h0
        1       R/W    auxadc_ck_en                    1'h0
        2       R/W    adc24b_func_en                  1'h0
        3       R/W    adc24b_ck_en                    1'h0
        4       R/W    RSVD                            1'h0
        5       R/W    RSVD                            1'h0
        6       R/W    keyscan_func_en                 1'h0
        7       R/W    keyscan_ck_en                   1'h0
        8       R/W    RSVD                            1'h0
        9       R/W    RSVD                            1'h0
        10      R/W    ppe_func_en                     1'h0
        11      R/W    ppe_ck_en                       1'h0
        12      R/W    gmac_func_en                    1'h0
        13      R/W    RSVD                            1'h0
        14      R/W    spi3w_func_en                   1'h0
        15      R/W    spi3w_ck_en                     1'h0
        16      R/W    RSVD                            1'h0
        17      R/W    RSVD                            1'h0
        18      R/W    segcom_func_en                  1'h0
        19      R/W    segcom_ck_en                    1'h0
        20      R/W    bt_mac_func_en                  1'h1
        21      R/W    bt_mac_ck_en                    1'h1
        22      R/W    bt_phy_func_en                  1'h0
        23      R/W    bt_phy_ck_en                    1'h0
        24      R/W    zb_mac_func_en                  1'h0
        25      R/W    zb_mac_ck_en                    1'h0
        26      R/W    bt_vendor_ck_en                 1'h1
        27      R/W    bt_cal32k_ck_en                 1'h0
        28      R/W    pdck_func_en                    1'h0
        29      R/W    pdck_ck_en                      1'h0
        30      R/W    aac_xtal_func_en                1'h0
        31      R/W    aac_xtal_ck_en                  1'h0
    */
    union
    {
        __IO uint32_t REG_GENERAL_PERI_CTL0;
        struct
        {
            __IO uint32_t auxadc_func_en: 1;
            __IO uint32_t auxadc_ck_en: 1;
            __IO uint32_t adc24b_func_en: 1;
            __IO uint32_t adc24b_ck_en: 1;
            __IO uint32_t RESERVED_6: 1;
            __IO uint32_t RESERVED_5: 1;
            __IO uint32_t keyscan_func_en: 1;
            __IO uint32_t keyscan_ck_en: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t ppe_func_en: 1;
            __IO uint32_t ppe_ck_en: 1;
            __IO uint32_t gmac_func_en: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t spi3w_func_en: 1;
            __IO uint32_t spi3w_ck_en: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t RESERVED_0: 1;
            __IO uint32_t segcom_func_en: 1;
            __IO uint32_t segcom_ck_en: 1;
            __IO uint32_t bt_mac_func_en: 1;
            __IO uint32_t bt_mac_ck_en: 1;
            __IO uint32_t bt_phy_func_en: 1;
            __IO uint32_t bt_phy_ck_en: 1;
            __IO uint32_t zb_mac_func_en: 1;
            __IO uint32_t zb_mac_ck_en: 1;
            __IO uint32_t bt_vendor_ck_en: 1;
            __IO uint32_t bt_cal32k_ck_en: 1;
            __IO uint32_t pdck_func_en: 1;
            __IO uint32_t pdck_ck_en: 1;
            __IO uint32_t aac_xtal_func_en: 1;
            __IO uint32_t aac_xtal_ck_en: 1;
        } BITS_31C;
    } u_31C;

    /* 0x320        0x4000_2320
        0       R/W    gpio_a_func_en                  1'h0
        1       R/W    gpio_a_ck_en                    1'h0
        2       R/W    gpio_a_deb_ck_en                1'h0
        3       R/W    gpio_a_deb_clk_sel              1'h0
        4       R/W    gpio_b_func_en                  1'h0
        5       R/W    gpio_b_ck_en                    1'h0
        6       R/W    gpio_b_deb_ck_en                1'h0
        7       R/W    gpio_b_deb_clk_sel              1'h0
        8       R/W    RSVD                            1'h0
        9       R/W    simc_ck_en                      1'h0
        10      R/W    simc_func_en                    1'h0
        11      R/W    RSVD                            1'h0
        12      R/W    RSVD                            1'h0
        13      R/W    RSVD                            1'h0
        14      R/W    RSVD                            1'h0
        15      R/W    r_ir_mux_clk_cg_en              1'h0
        16      R/W    r_pll_ir_div_sel                1'h0
        17      R/W    r_pll_ir_src_sel                1'h0
        18      R/W    r_sclk_ir_src_sel               1'h0
        19      R/W    ir_ck_en                        1'h0
        20      R/W    ir_func_en                      1'h0
        22:21   R/W    r_can_lp_scan_div_sel           2'h0
        23      R/W    r_can_scan_div_sel              1'h0
        24      R/W    can_ck_en                       1'h0
        25      R/W    can_func_en                     1'h0
        29:26   R/W    RSVD                            4'h0
        30      R/W    RSVD                            1'h0
        31      R/W    RSVD                            1'h0
    */
    union
    {
        __IO uint32_t REG_GENERAL_PERI_CTL1;
        struct
        {
            __IO uint32_t gpio_a_func_en: 1;
            __IO uint32_t gpio_a_ck_en: 1;
            __IO uint32_t gpio_a_deb_ck_en: 1;
            __IO uint32_t gpio_a_deb_clk_sel: 1;
            __IO uint32_t gpio_b_func_en: 1;
            __IO uint32_t gpio_b_ck_en: 1;
            __IO uint32_t gpio_b_deb_ck_en: 1;
            __IO uint32_t gpio_b_deb_clk_sel: 1;
            __IO uint32_t RESERVED_7: 1;
            __IO uint32_t simc_ck_en: 1;
            __IO uint32_t simc_func_en: 1;
            __IO uint32_t RESERVED_6: 1;
            __IO uint32_t RESERVED_5: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t r_ir_mux_clk_cg_en: 1;
            __IO uint32_t r_pll_ir_div_sel: 1;
            __IO uint32_t r_pll_ir_src_sel: 1;
            __IO uint32_t r_sclk_ir_src_sel: 1;
            __IO uint32_t ir_ck_en: 1;
            __IO uint32_t ir_func_en: 1;
            __IO uint32_t r_can_lp_scan_div_sel: 2;
            __IO uint32_t r_can_scan_div_sel: 1;
            __IO uint32_t can_ck_en: 1;
            __IO uint32_t can_func_en: 1;
            __IO uint32_t RESERVED_2: 4;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t RESERVED_0: 1;
        } BITS_320;
    } u_320;

    /* 0x324        0x4000_2324
        2:0     R/W    RSVD                            1'h0
        3       R/W    RSVD                            1'h0
        4       R/W    RSVD                            1'h0
        5       R/W    RSVD                            1'h0
        6       R/W    RSVD                            1'h0
        7       R/W    rtzip_ck_en                     1'h0
        8       R/W    rtzip_func_en                   1'h0
        15:9    R/W    RSVD                            7'h0
        18:16   R/W    r_disp_div_sel                  3'h0
        19      R/W    r_disp_div_en                   1'h0
        20      R/W    r_disp_mux_clk_cg_en            1'h0
        21      R/W    r_disp_clk_src_sel1             1'h0
        22      R/W    r_disp_clk_src_sel0             1'h0
        23      R/W    disp_ck_en                      1'h0
        24      R/W    disp_func_en                    1'h0
        31:25   R/W    RSVD                            7'h0
    */
    union
    {
        __IO uint32_t REG_GENERAL_PERI_CTL2;
        struct
        {
            __IO uint32_t RESERVED_6: 3;
            __IO uint32_t RESERVED_5: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t rtzip_ck_en: 1;
            __IO uint32_t rtzip_func_en: 1;
            __IO uint32_t RESERVED_1: 7;
            __IO uint32_t r_disp_div_sel: 3;
            __IO uint32_t r_disp_div_en: 1;
            __IO uint32_t r_disp_mux_clk_cg_en: 1;
            __IO uint32_t r_disp_clk_src_sel1: 1;
            __IO uint32_t r_disp_clk_src_sel0: 1;
            __IO uint32_t disp_ck_en: 1;
            __IO uint32_t disp_func_en: 1;
            __IO uint32_t RESERVED_0: 7;
        } BITS_324;
    } u_324;

    /* 0x328        0x4000_2328
        2:0     R/W    r_timer_1_div_sel               3'h0
        3       R/W    r_timer_1_div_en                1'h0
        4       R/W    RSVD                            1'h0
        7:5     R/W    RSVD                            3'h0
        8       R/W    RSVD                            1'h0
        9       R/W    RSVD                            1'h0
        10      R/W    RSVD                            1'h0
        11      R/W    RSVD                            1'h0
        15:12   R/W    RSVD                            4'h0
        18:16   R/W    r_timer_2_div_sel               3'h0
        19      R/W    r_timer_2_div_en                1'h0
        20      R/W    RSVD                            1'h0
        23:21   R/W    RSVD                            3'h0
        24      R/W    RSVD                            1'h0
        25      R/W    RSVD                            1'h0
        26      R/W    RSVD                            1'h0
        27      R/W    RSVD                            1'h0
        28      R/W    RSVD                            1'h0
        29      R/W    slv_clk_timer_apb_g             1'h0
        30      R/W    r_timer_func_en                 1'h0
        31      R/W    r_timer_ck_en                   1'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_0_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_timer_1_div_sel: 3;
            __IO uint32_t r_timer_1_div_en: 1;
            __IO uint32_t RESERVED_13: 1;
            __IO uint32_t RESERVED_12: 3;
            __IO uint32_t RESERVED_11: 1;
            __IO uint32_t RESERVED_10: 1;
            __IO uint32_t RESERVED_9: 1;
            __IO uint32_t RESERVED_8: 1;
            __IO uint32_t RESERVED_7: 4;
            __IO uint32_t r_timer_2_div_sel: 3;
            __IO uint32_t r_timer_2_div_en: 1;
            __IO uint32_t RESERVED_6: 1;
            __IO uint32_t RESERVED_5: 3;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t RESERVED_0: 1;
            __IO uint32_t slv_clk_timer_apb_g: 1;
            __IO uint32_t r_timer_func_en: 1;
            __IO uint32_t r_timer_ck_en: 1;
        } BITS_328;
    } u_328;

    /* 0x32C        0x4000_232c
        2:0     R/W    r_timer_3_div_sel               3'h0
        3       R/W    r_timer_3_div_en                1'h0
        4       R/W    r_timer_3_clk_sel2              1'h0
        8:5     R/W    RSVD                            4'h0
        9       R/W    r_timer_pwm_wrap3_clk_sel       1'h0
        10      R/W    r_timer_pwm_wrap3_func_en       1'h0
        11      R/W    r_timer_pwm_wrap3_ck_en         1'h0
        12      R/W    r_timer_3_clk_sel1              1'h0
        13      R/W    r_timer_3_clk_sel0              1'h0
        15:14   R/W    RSVD                            2'h0
        18:16   R/W    r_timer_4_div_sel               3'h0
        19      R/W    r_timer_4_div_en                1'h0
        20      R/W    r_timer_4_clk_sel2              1'h0
        24:21   R/W    RSVD                            4'h0
        25      R/W    r_timer_pwm_wrap4_clk_sel       1'h0
        26      R/W    r_timer_pwm_wrap4_func_en       1'h0
        27      R/W    r_timer_pwm_wrap4_ck_en         1'h0
        28      R/W    r_timer_4_clk_sel1              1'h0
        29      R/W    r_timer_4_clk_sel0              1'h0
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_1_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_timer_3_div_sel: 3;
            __IO uint32_t r_timer_3_div_en: 1;
            __IO uint32_t r_timer_3_clk_sel2: 1;
            __IO uint32_t RESERVED_3: 4;
            __IO uint32_t r_timer_pwm_wrap3_clk_sel: 1;
            __IO uint32_t r_timer_pwm_wrap3_func_en: 1;
            __IO uint32_t r_timer_pwm_wrap3_ck_en: 1;
            __IO uint32_t r_timer_3_clk_sel1: 1;
            __IO uint32_t r_timer_3_clk_sel0: 1;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t r_timer_4_div_sel: 3;
            __IO uint32_t r_timer_4_div_en: 1;
            __IO uint32_t r_timer_4_clk_sel2: 1;
            __IO uint32_t RESERVED_1: 4;
            __IO uint32_t r_timer_pwm_wrap4_clk_sel: 1;
            __IO uint32_t r_timer_pwm_wrap4_func_en: 1;
            __IO uint32_t r_timer_pwm_wrap4_ck_en: 1;
            __IO uint32_t r_timer_4_clk_sel1: 1;
            __IO uint32_t r_timer_4_clk_sel0: 1;
            __IO uint32_t RESERVED_0: 2;
        } BITS_32C;
    } u_32C;

    /* 0x330        0x4000_2330
        2:0     R/W    r_timer_5_div_sel               3'h0
        3       R/W    r_timer_5_div_en                1'h0
        4       R/W    r_timer_5_clk_sel2              1'h0
        11:5    R/W    RSVD                            7'h0
        12      R/W    r_timer_5_clk_sel1              1'h0
        13      R/W    r_timer_5_clk_sel0              1'h0
        15:14   R/W    RSVD                            2'h0
        18:16   R/W    r_timer_6_div_sel               3'h0
        19      R/W    r_timer_6_div_en                1'h0
        20      R/W    r_timer_6_clk_sel2              1'h0
        27:21   R/W    RSVD                            7'h0
        28      R/W    r_timer_6_clk_sel1              1'h0
        29      R/W    r_timer_6_clk_sel0              1'h0
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_2_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_timer_5_div_sel: 3;
            __IO uint32_t r_timer_5_div_en: 1;
            __IO uint32_t r_timer_5_clk_sel2: 1;
            __IO uint32_t RESERVED_3: 7;
            __IO uint32_t r_timer_5_clk_sel1: 1;
            __IO uint32_t r_timer_5_clk_sel0: 1;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t r_timer_6_div_sel: 3;
            __IO uint32_t r_timer_6_div_en: 1;
            __IO uint32_t r_timer_6_clk_sel2: 1;
            __IO uint32_t RESERVED_1: 7;
            __IO uint32_t r_timer_6_clk_sel1: 1;
            __IO uint32_t r_timer_6_clk_sel0: 1;
            __IO uint32_t RESERVED_0: 2;
        } BITS_330;
    } u_330;

    /* 0x334        0x4000_2334
        2:0     R/W    r_timer_7_div_sel               3'h0
        3       R/W    r_timer_7_div_en                1'h0
        4       R/W    r_timer_7_clk_sel2              1'h0
        11:5    R/W    RSVD                            7'h0
        12      R/W    r_timer_7_clk_sel1              1'h0
        13      R/W    r_timer_7_clk_sel0              1'h0
        15:14   R/W    RSVD                            2'h0
        18:16   R/W    r_timer_8_div_sel               3'h0
        19      R/W    r_timer_8_div_en                1'h0
        20      R/W    r_timer_8_clk_sel2              1'h0
        27:21   R/W    RSVD                            7'h0
        28      R/W    r_timer_8_clk_sel1              1'h0
        29      R/W    r_timer_8_clk_sel0              1'h0
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_3_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_timer_7_div_sel: 3;
            __IO uint32_t r_timer_7_div_en: 1;
            __IO uint32_t r_timer_7_clk_sel2: 1;
            __IO uint32_t RESERVED_3: 7;
            __IO uint32_t r_timer_7_clk_sel1: 1;
            __IO uint32_t r_timer_7_clk_sel0: 1;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t r_timer_8_div_sel: 3;
            __IO uint32_t r_timer_8_div_en: 1;
            __IO uint32_t r_timer_8_clk_sel2: 1;
            __IO uint32_t RESERVED_1: 7;
            __IO uint32_t r_timer_8_clk_sel1: 1;
            __IO uint32_t r_timer_8_clk_sel0: 1;
            __IO uint32_t RESERVED_0: 2;
        } BITS_334;
    } u_334;

    /* 0x338        0x4000_2338
        31:0    R/W    RSVD                           32'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_PWM_WRAP_0_CFG;
        struct
        {
            __IO uint32_t RESERVED_0: 32;
        } BITS_338;
    } u_338;

    /* 0x33C        0x4000_233c
        7:0     R/W    timer_pwm_3_dead_zone_size      8'h0
        8       R/W    timer_pwm_3_emg_stop            1'h0
        9       R/W    timer_pwm_3_stop_state[0]       1'h0
        10      R/W    timer_pwm_3_stop_state[1]       1'h0
        11      R/W    timer_pwm_3_dummy_b11           1'h0
        12      R/W    timer_pwm_3_dead_zone_en        1'h0
        13      R/W    timer_pwm_3_pwm_pn_invserse_sel 1'h0
        14      R/W    timer_pwm_3_dummy_b14           1'h0
        15      R/W    timer_pwm_3_dummy_b15           1'h0
        23:16   R/W    timer_pwm_4_dead_zone_size      8'h0
        24      R/W    timer_pwm_4_emg_stop            1'h0
        25      R/W    timer_pwm_4_stop_state[0]       1'h0
        26      R/W    timer_pwm_4_stop_state[1]       1'h0
        27      R/W    timer_pwm_4_dummy_b11           1'h0
        28      R/W    timer_pwm_4_dead_zone_en        1'h0
        29      R/W    timer_pwm_4_pwm_pn_invserse_sel 1'h0
        30      R/W    timer_pwm_4_dummy_b14           1'h0
        31      R/W    timer_pwm_4_dummy_b15           1'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_PWM_WRAP_1_CFG;
        struct
        {
            __IO uint32_t timer_pwm_3_dead_zone_size: 8;
            __IO uint32_t timer_pwm_3_emg_stop: 1;
            __IO uint32_t timer_pwm_3_stop_state_0: 1;
            __IO uint32_t timer_pwm_3_stop_state_1: 1;
            __IO uint32_t timer_pwm_3_dummy_b11: 1;
            __IO uint32_t timer_pwm_3_dead_zone_en: 1;
            __IO uint32_t timer_pwm_3_pwm_pn_invserse_sel: 1;
            __IO uint32_t timer_pwm_3_dummy_b14: 1;
            __IO uint32_t timer_pwm_3_dummy_b15: 1;
            __IO uint32_t timer_pwm_4_dead_zone_size: 8;
            __IO uint32_t timer_pwm_4_emg_stop: 1;
            __IO uint32_t timer_pwm_4_stop_state_0: 1;
            __IO uint32_t timer_pwm_4_stop_state_1: 1;
            __IO uint32_t timer_pwm_4_dummy_b11: 1;
            __IO uint32_t timer_pwm_4_dead_zone_en: 1;
            __IO uint32_t timer_pwm_4_pwm_pn_invserse_sel: 1;
            __IO uint32_t timer_pwm_4_dummy_b14: 1;
            __IO uint32_t timer_pwm_4_dummy_b15: 1;
        } BITS_33C;
    } u_33C;

    /* 0x340        0x4000_2340
        31:0    R/W    RSVD                            32'h0
    */
    union
    {
        __IO uint32_t REG_TIMER_PWM_WRAP_2_CFG;
        struct
        {
            __IO uint32_t RESERVED_0: 32;
        } BITS_340;
    } u_340;

    /* 0x344        0x4000_2344
        2:0     R/W    r_etimer_0_div_sel              3'h0
        3       R/W    r_etimer_0_div_en               1'h0
        4       R/W    r_etimer_01_clk_src_sel2        1'h0
        5       R/W    r_etimer_01_clk_src_sel1        1'h0
        6       R/W    r_etimer_01_clk_src_sel0        1'h0
        9:7     R/W    r_etimer_pwm_0_div_sel          3'h0
        10      R/W    r_etimer_pwm_0_div_en           1'h0
        11      R/W    r_etimer_pwm_0_clk_src_sel      1'h0
        12      R/W    r_etimer_pwm_0_func_en          1'h0
        13      R/W    r_etimer_pwm_0_ck_en            1'h0
        15:14   R/W    RSVD                            2'h0
        18:16   R/W    r_etimer_1_div_sel              3'h0
        19      R/W    r_etimer_1_div_en               1'h0
        22:20   R/W    RSVD                            3'h0
        25:23   R/W    r_etimer_pwm_1_div_sel          3'h0
        26      R/W    r_etimer_pwm_1_div_en           1'h0
        27      R/W    r_etimer_pwm_1_clk_src_sel      1'h0
        28      R/W    r_etimer_pwm_1_func_en          1'h0
        29      R/W    r_etimer_pwm_1_ck_en            1'h0
        30      R/W    r_etimer_func_en                1'h0
        31      R/W    r_etimer_ck_en                  1'h0
    */
    union
    {
        __IO uint32_t REG_ENHTIMER_1_0_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_etimer_0_div_sel: 3;
            __IO uint32_t r_etimer_0_div_en: 1;
            __IO uint32_t r_etimer_01_clk_src_sel2: 1;
            __IO uint32_t r_etimer_01_clk_src_sel1: 1;
            __IO uint32_t r_etimer_01_clk_src_sel0: 1;
            __IO uint32_t r_etimer_pwm_0_div_sel: 3;
            __IO uint32_t r_etimer_pwm_0_div_en: 1;
            __IO uint32_t r_etimer_pwm_0_clk_src_sel: 1;
            __IO uint32_t r_etimer_pwm_0_func_en: 1;
            __IO uint32_t r_etimer_pwm_0_ck_en: 1;
            __IO uint32_t RESERVED_1: 2;
            __IO uint32_t r_etimer_1_div_sel: 3;
            __IO uint32_t r_etimer_1_div_en: 1;
            __IO uint32_t RESERVED_0: 3;
            __IO uint32_t r_etimer_pwm_1_div_sel: 3;
            __IO uint32_t r_etimer_pwm_1_div_en: 1;
            __IO uint32_t r_etimer_pwm_1_clk_src_sel: 1;
            __IO uint32_t r_etimer_pwm_1_func_en: 1;
            __IO uint32_t r_etimer_pwm_1_ck_en: 1;
            __IO uint32_t r_etimer_func_en: 1;
            __IO uint32_t r_etimer_ck_en: 1;
        } BITS_344;
    } u_344;

    /* 0x348        0x4000_2348
        2:0     R/W    r_etimer_2_div_sel              3'h0
        3       R/W    r_etimer_2_div_en               1'h0
        4       R/W    r_etimer_23_clk_src_sel2        1'h0
        5       R/W    r_etimer_23_clk_src_sel1        1'h0
        6       R/W    r_etimer_23_clk_src_sel0        1'h0
        9:7     R/W    r_etimer_pwm_2_div_sel          3'h0
        10      R/W    r_etimer_pwm_2_div_en           1'h0
        11      R/W    r_etimer_pwm_2_clk_src_sel      1'h0
        12      R/W    r_etimer_pwm_2_func_en          1'h0
        13      R/W    r_etimer_pwm_2_ck_en            1'h0
        15:14   R/W    RSVD                            2'h0
        18:16   R/W    r_etimer_3_div_sel              3'h0
        19      R/W    r_etimer_3_div_en               1'h0
        22:20   R/W    RSVD                            3'h0
        25:23   R/W    r_etimer_pwm_3_div_sel          3'h0
        26      R/W    r_etimer_pwm_3_div_en           1'h0
        27      R/W    r_etimer_pwm_3_clk_src_sel      1'h0
        28      R/W    r_etimer_pwm_3_func_en          1'h0
        29      R/W    r_etimer_pwm_3_ck_en            1'h0
        31:30   R/W    RSVD                            2'h0
    */
    union
    {
        __IO uint32_t REG_ENHTIMER_3_2_CLOCK_CTRL;
        struct
        {
            __IO uint32_t r_etimer_2_div_sel: 3;
            __IO uint32_t r_etimer_2_div_en: 1;
            __IO uint32_t r_etimer_23_clk_src_sel2: 1;
            __IO uint32_t r_etimer_23_clk_src_sel1: 1;
            __IO uint32_t r_etimer_23_clk_src_sel0: 1;
            __IO uint32_t r_etimer_pwm_2_div_sel: 3;
            __IO uint32_t r_etimer_pwm_2_div_en: 1;
            __IO uint32_t r_etimer_pwm_2_clk_src_sel: 1;
            __IO uint32_t r_etimer_pwm_2_func_en: 1;
            __IO uint32_t r_etimer_pwm_2_ck_en: 1;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t r_etimer_3_div_sel: 3;
            __IO uint32_t r_etimer_3_div_en: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t r_etimer_pwm_3_div_sel: 3;
            __IO uint32_t r_etimer_pwm_3_div_en: 1;
            __IO uint32_t r_etimer_pwm_3_clk_src_sel: 1;
            __IO uint32_t r_etimer_pwm_3_func_en: 1;
            __IO uint32_t r_etimer_pwm_3_ck_en: 1;
            __IO uint32_t RESERVED_0: 2;
        } BITS_348;
    } u_348;

    /* 0x34C        0x4000_234c
        7:0     R/W    GPIOA_G0_CNT_LIMIT              8'h1
        8       R/W    GPIOA_G0_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOA_G0_DEB_CLK_DIV            3'h0
        12      R/W    GPIOA_G0_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOA_G1_CNT_LIMIT              8'h1
        24      R/W    GPIOA_G1_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOA_G1_DEB_CLK_DIV            3'h0
        28      R/W    GPIOA_G1_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOA_DEB_CLK_CTL_0;
        struct
        {
            __IO uint32_t GPIOA_G0_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G0_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G0_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G0_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOA_G1_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G1_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G1_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G1_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_34C;
    } u_34C;

    /* 0x350        0x4000_2350
        7:0     R/W    GPIOA_G2_CNT_LIMIT              8'h1
        8       R/W    GPIOA_G2_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOA_G2_DEB_CLK_DIV            3'h0
        12      R/W    GPIOA_G2_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOA_G3_CNT_LIMIT              8'h1
        24      R/W    GPIOA_G3_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOA_G3_DEB_CLK_DIV            3'h0
        28      R/W    GPIOA_G3_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOA_DEB_CLK_CTL_1;
        struct
        {
            __IO uint32_t GPIOA_G2_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G2_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G2_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G2_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOA_G3_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G3_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G3_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G3_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_350;
    } u_350;

    /* 0x354        0x4000_2354
        7:0     R/W    GPIOA_G4_CNT_LIMIT              8'h1
        8       R/W    GPIOA_G4_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOA_G4_DEB_CLK_DIV            3'h0
        12      R/W    GPIOA_G4_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOA_G5_CNT_LIMIT              8'h1
        24      R/W    GPIOA_G5_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOA_G5_DEB_CLK_DIV            3'h0
        28      R/W    GPIOA_G5_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOA_DEB_CLK_CTL_2;
        struct
        {
            __IO uint32_t GPIOA_G4_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G4_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G4_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G4_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOA_G5_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G5_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G5_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G5_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_354;
    } u_354;

    /* 0x358        0x4000_2358
        7:0     R/W    GPIOA_G6_CNT_LIMIT              8'h1
        8       R/W    GPIOA_G6_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOA_G6_DEB_CLK_DIV            3'h0
        12      R/W    GPIOA_G6_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOA_G7_CNT_LIMIT              8'h1
        24      R/W    GPIOA_G7_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOA_G7_DEB_CLK_DIV            3'h0
        28      R/W    GPIOA_G7_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOA_DEB_CLK_CTL_3;
        struct
        {
            __IO uint32_t GPIOA_G6_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G6_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G6_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G6_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOA_G7_CNT_LIMIT: 8;
            __IO uint32_t GPIOA_G7_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOA_G7_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOA_G7_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_358;
    } u_358;

    /* 0x35C        0x4000_235c
        31:0    R/W    GPIOA_x_DEB_FUNC_EN             32'h0
    */
    union
    {
        __IO uint32_t GPIOA_DEB_FUN_CTL;
        struct
        {
            __IO uint32_t GPIOA_x_DEB_FUNC_EN: 32;
        } BITS_35C;
    } u_35C;

    /* 0x360        0x4000_2360
        7:0     R/W    GPIOB_G0_CNT_LIMIT              8'h1
        8       R/W    GPIOB_G0_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOB_G0_DEB_CLK_DIV            3'h0
        12      R/W    GPIOB_G0_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOB_G1_CNT_LIMIT              8'h1
        24      R/W    GPIOB_G1_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOB_G1_DEB_CLK_DIV            3'h0
        28      R/W    GPIOB_G1_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOB_DEB_CLK_CTL_0;
        struct
        {
            __IO uint32_t GPIOB_G0_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G0_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G0_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G0_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOB_G1_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G1_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G1_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G1_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_360;
    } u_360;

    /* 0x364        0x4000_2364
        7:0     R/W    GPIOB_G2_CNT_LIMIT              8'h1
        8       R/W    GPIOB_G2_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOB_G2_DEB_CLK_DIV            3'h0
        12      R/W    GPIOB_G2_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOB_G3_CNT_LIMIT              8'h1
        24      R/W    GPIOB_G3_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOB_G3_DEB_CLK_DIV            3'h0
        28      R/W    GPIOB_G3_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOB_DEB_CLK_CTL_1;
        struct
        {
            __IO uint32_t GPIOB_G2_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G2_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G2_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G2_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOB_G3_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G3_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G3_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G3_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_364;
    } u_364;

    /* 0x368        0x4000_2368
        7:0     R/W    GPIOB_G4_CNT_LIMIT              8'h1
        8       R/W    GPIOB_G4_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOB_G4_DEB_CLK_DIV            3'h0
        12      R/W    GPIOB_G4_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOB_G5_CNT_LIMIT              8'h1
        24      R/W    GPIOB_G5_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOB_G5_DEB_CLK_DIV            3'h0
        28      R/W    GPIOB_G5_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOB_DEB_CLK_CTL_2;
        struct
        {
            __IO uint32_t GPIOB_G4_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G4_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G4_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G4_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOB_G5_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G5_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G5_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G5_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_368;
    } u_368;

    /* 0x36C        0x4000_236c
        7:0     R/W    GPIOB_G6_CNT_LIMIT              8'h1
        8       R/W    GPIOB_G6_DEB_CLK_SEL            1'h0
        11:9    R/W    GPIOB_G6_DEB_CLK_DIV            3'h0
        12      R/W    GPIOB_G6_DEB_CNT_EN             1'b0
        15:13   R/W    RSVD                            3'h0
        23:16   R/W    GPIOB_G7_CNT_LIMIT              8'h1
        24      R/W    GPIOB_G7_DEB_CLK_SEL            1'h0
        27:25   R/W    GPIOB_G7_DEB_CLK_DIV            3'h0
        28      R/W    GPIOB_G7_DEB_CNT_EN             1'b0
        31:29   R/W    RSVD                            3'h0
    */
    union
    {
        __IO uint32_t GPIOB_DEB_CLK_CTL_3;
        struct
        {
            __IO uint32_t GPIOB_G6_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G6_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G6_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G6_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_1: 3;
            __IO uint32_t GPIOB_G7_CNT_LIMIT: 8;
            __IO uint32_t GPIOB_G7_DEB_CLK_SEL: 1;
            __IO uint32_t GPIOB_G7_DEB_CLK_DIV: 3;
            __IO uint32_t GPIOB_G7_DEB_CNT_EN: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_36C;
    } u_36C;

    /* 0x370        0x4000_2370
        31:0    R/W    GPIOB_x_DEB_FUNC_EN             32'h0
    */
    union
    {
        __IO uint32_t GPIOB_DEB_FUN_CTL;
        struct
        {
            __IO uint32_t GPIOB_x_DEB_FUNC_EN: 32;
        } BITS_370;
    } u_370;

    /* 0x374        0x4000_2374
        0       R/W    sdio_ck_en                      1'h0
        1       R/W    sdio_func_en                    1'h0
        2       R/W    r_sdio_clk_src_en               1'h0
        6:3     R/W    r_sdio_div_sel                  4'h0
        7       R/W    r_sdio_div_en                   1'h0
        8       R/W    r_sdio_mux_clk_cg_en            1'h0
        9       R/W    r_sdio_clk_src_sel1             1'h0
        10      R/W    r_sdio_clk_src_sel0             1'h0
        31:11   R/W    RSVD                            21'h0
    */
    union
    {
        __IO uint32_t REG_SDH_CTL;
        struct
        {
            __IO uint32_t sdio_ck_en: 1;
            __IO uint32_t sdio_func_en: 1;
            __IO uint32_t r_sdio_clk_src_en: 1;
            __IO uint32_t r_sdio_div_sel: 4;
            __IO uint32_t r_sdio_div_en: 1;
            __IO uint32_t r_sdio_mux_clk_cg_en: 1;
            __IO uint32_t r_sdio_clk_src_sel1: 1;
            __IO uint32_t r_sdio_clk_src_sel0: 1;
            __IO uint32_t RESERVED_0: 21;
        } BITS_374;
    } u_374;

    /* 0x378        0x4000_2378
        7:0     R/W    r_sdh_drv_dly_sel               8'h0
        15:8    R/W    r_sdh_sample_dly_sel            8'h0
        17:16   R/W    r_sdh_clk_sel_drv               2'h0
        19:18   R/W    r_sdh_clk_sel_sample            2'h0
        20      R/W    r_sdh_bypass_shift_drv          1'h0
        21      R/W    r_sdh_bypass_shift_sample       1'h0
        22      R/W    r_sdh_bypass_delay_drv          1'h0
        23      R/W    r_sdh_bypass_delay_sample       1'h0
        31:24   R/W    r_sdh_clk_out_dly_sel           8'h0
    */
    union
    {
        __IO uint32_t REG_SDH_PHY0;
        struct
        {
            __IO uint32_t r_sdh_drv_dly_sel: 8;
            __IO uint32_t r_sdh_sample_dly_sel: 8;
            __IO uint32_t r_sdh_clk_sel_drv: 2;
            __IO uint32_t r_sdh_clk_sel_sample: 2;
            __IO uint32_t r_sdh_bypass_shift_drv: 1;
            __IO uint32_t r_sdh_bypass_shift_sample: 1;
            __IO uint32_t r_sdh_bypass_delay_drv: 1;
            __IO uint32_t r_sdh_bypass_delay_sample: 1;
            __IO uint32_t r_sdh_clk_out_dly_sel: 8;
        } BITS_378;
    } u_378;

    /* 0x37C        0x4000_237c
        7:0     R/W    r_sdh_cmd_out_dly_sel           8'h0
        15:8    R/W    r_sdh_dat0_dly_sel              8'h0
        23:16   R/W    r_sdh_dat1_dly_sel              8'h0
        31:24   R/W    r_sdh_dat2_dly_sel              8'h0
    */
    union
    {
        __IO uint32_t REG_SDH_PHY1;
        struct
        {
            __IO uint32_t r_sdh_cmd_out_dly_sel: 8;
            __IO uint32_t r_sdh_dat0_dly_sel: 8;
            __IO uint32_t r_sdh_dat1_dly_sel: 8;
            __IO uint32_t r_sdh_dat2_dly_sel: 8;
        } BITS_37C;
    } u_37C;

    /* 0x380        0x4000_2380
        7:0     R/W    r_sdh_dat3_dly_sel              8'h0
        15:8    R/W    r_sdh_dat4_dly_sel              8'h0
        23:16   R/W    r_sdh_dat5_dly_sel              8'h0
        31:24   R/W    r_sdh_dat6_dly_sel              8'h0
    */
    union
    {
        __IO uint32_t REG_SDH_PHY2;
        struct
        {
            __IO uint32_t r_sdh_dat3_dly_sel: 8;
            __IO uint32_t r_sdh_dat4_dly_sel: 8;
            __IO uint32_t r_sdh_dat5_dly_sel: 8;
            __IO uint32_t r_sdh_dat6_dly_sel: 8;
        } BITS_380;
    } u_380;

    /* 0x384        0x4000_2384
        7:0     R/W    r_sdh_dat7_dly_sel              8'h0
        19:8    R/W    r_sdh_dbg_sel                   12'h0
        21:20   R/W    r_sdh_dbg_en_i                  2'h0
        22      R/W    r_sdh_cclk_in_drv               1'h0
        23      R/W    r_sdh_cclk_sample_drv           1'h0
        24      R/W    r_sdh_cclk_in_div_enable        1'h1
        31:25   R/W    RSVD                            7'h0
    */
    union
    {
        __IO uint32_t REG_SDH_PHY3;
        struct
        {
            __IO uint32_t r_sdh_dat7_dly_sel: 8;
            __IO uint32_t r_sdh_dbg_sel: 12;
            __IO uint32_t r_sdh_dbg_en_i: 2;
            __IO uint32_t r_sdh_cclk_in_drv: 1;
            __IO uint32_t r_sdh_cclk_sample_drv: 1;
            __IO uint32_t r_sdh_cclk_in_div_enable: 1;
            __IO uint32_t RESERVED_0: 7;
        } BITS_384;
    } u_384;

    /* 0x388        0x4000_2388
        5:0     R/W    r_bt_ahb_wait_cnt               6'hC
        31:6    R/W    RSVD                            26'h0
    */
    union
    {
        __IO uint32_t REG_BT_MISC;
        struct
        {
            __IO uint32_t r_bt_ahb_wait_cnt: 6;
            __IO uint32_t RESERVED_0: 26;
        } BITS_388;
    } u_388;

    /* 0x38C        0x4000_238c
        0       R/W    r_PMUX_1_WIRE_UART4_EN          1'h0
        1       R/W    rtk_uart4_func_en               1'h0
        2       R/W    rtk_uart4_ck_en                 1'h0
        3       R/W    rtk_uart4_div_en                1'h0
        6:4     R/W    rtk_uart4_div_sel               3'b000
        7       R/W    RSVD                            1'h0
        8       R/W    r_PMUX_1_WIRE_UART5_EN          1'h0
        9       R/W    rtk_uart5_func_en               1'h0
        10      R/W    rtk_uart5_ck_en                 1'h0
        11      R/W    rtk_uart5_div_en                1'h0
        14:12   R/W    rtk_uart5_div_sel               3'b000
        31:15   R/W    RSVD                            17'h0
    */
    union
    {
        __IO uint32_t REG_UART_PERI_CTL1;
        struct
        {
            __IO uint32_t r_PMUX_1_WIRE_UART4_EN: 1;
            __IO uint32_t rtk_uart4_func_en: 1;
            __IO uint32_t rtk_uart4_ck_en: 1;
            __IO uint32_t rtk_uart4_div_en: 1;
            __IO uint32_t rtk_uart4_div_sel: 3;
            __IO uint32_t RESERVED_13: 1;
            __IO uint32_t r_PMUX_1_WIRE_UART5_EN: 1;
            __IO uint32_t rtk_uart5_func_en: 1;
            __IO uint32_t rtk_uart5_ck_en: 1;
            __IO uint32_t rtk_uart5_div_en: 1;
            __IO uint32_t rtk_uart5_div_sel: 3;
            __IO uint32_t RESERVED_0: 17;
        } BITS_38C;
    } u_38C;

    /* 0x390        0x4000_2390
        1:0     R/W    GMAC_LX_BUS_TIMEOUT_THRESHOLD   2'h0
        2       R/W    GMAC_LX_BUS_TIMEOUT_EN          1'h0
        3       R/W    GMAC_LX_BUS_DMA_LOCK_IN         1'h0
        5:4     R/W    GMAC_MII_LX_TIMEOUT_THRESHOLD   2'h0
        6       R/W    GMAC_MII_LX_TIMEOUT_EN          1'h0
        31:7    R/W    RSVD                            25'b0
    */
    union
    {
        __IO uint32_t REG_GMAC_BUS;
        struct
        {
            __IO uint32_t GMAC_LX_BUS_TIMEOUT_THRESHOLD: 2;
            __IO uint32_t GMAC_LX_BUS_TIMEOUT_EN: 1;
            __IO uint32_t GMAC_LX_BUS_DMA_LOCK_IN: 1;
            __IO uint32_t GMAC_MII_LX_TIMEOUT_THRESHOLD: 2;
            __IO uint32_t GMAC_MII_LX_TIMEOUT_EN: 1;
            __IO uint32_t RESERVED_0: 25;
        } BITS_390;
    } u_390;

    /* 0x394        0x4000_2394
        18:0    R/W    gmac_base_addr                  19'h20020
        31:19   R/W    RSVD                            13'b0
    */
    union
    {
        __IO uint32_t REG_GMAC_BASE_ADDR;
        struct
        {
            __IO uint32_t gmac_base_addr: 19;
            __IO uint32_t RESERVED_0: 13;
        } BITS_394;
    } u_394;

    /* 0x398        0x4000_2398
        18:0    R/W    gmac_base_addr_1                19'h28020
        31:19   R/W    RSVD                            13'b0
    */
    union
    {
        __IO uint32_t REG_GMAC_BASE_ADDR_1;
        struct
        {
            __IO uint32_t gmac_base_addr_1: 19;
            __IO uint32_t RESERVED_0: 13;
        } BITS_398;
    } u_398;

    /* 0x39C        0x4000_239c
        5:0     R/W    gmac2fephy_phy_ad               6'b0
        31:6    R/W    RSVD                            26'b0
    */
    union
    {
        __IO uint32_t REG_GMAC_PHY_AD;
        struct
        {
            __IO uint32_t gmac2fephy_phy_ad: 6;
            __IO uint32_t RESERVED_0: 26;
        } BITS_39C;
    } u_39C;

    /* 0x3A0        0x4000_23a0
        31:0    R/W    r_sdh0_phy_dbg                  32'h0
    */
    union
    {
        __IO uint32_t REG_SDH0_DBG0;
        struct
        {
            __IO uint32_t r_sdh0_phy_dbg: 32;
        } BITS_3A0;
    } u_3A0;

    /* 0x3A4        0x4000_23a4
        31:0    R/W    r_sdh0_dbg                      32'h0
    */
    union
    {
        __IO uint32_t REG_SDH0_DBG1;
        struct
        {
            __IO uint32_t r_sdh0_dbg: 32;
        } BITS_3A4;
    } u_3A4;

    /* 0x3A8        0x4000_23a8
        7:0     R/W    r_sdh0_cmd_out_oe_dly_sel       8'h0
        15:8    R/W    r_sdh0_dat0_oe_dly_sel          8'h0
        23:16   R/W    r_sdh0_dat1_oe_dly_sel          8'h0
        31:24   R/W    r_sdh0_dat2_oe_dly_sel          8'h0
    */
    union
    {
        __IO uint32_t REG_SDH0_PHY4;
        struct
        {
            __IO uint32_t r_sdh0_cmd_out_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat0_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat1_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat2_oe_dly_sel: 8;
        } BITS_3A8;
    } u_3A8;

    /* 0x3AC        0x4000_23ac
        7:0     R/W    r_sdh0_dat3_oe_dly_sel          8'h0
        15:8    R/W    r_sdh0_dat4_oe_dly_sel          8'h0
        23:16   R/W    r_sdh0_dat5_oe_dly_sel          8'h0
        31:24   R/W    r_sdh0_dat6_oe_dly_sel          8'h0
    */
    union
    {
        __IO uint32_t REG_SDIO0_PHY5;
        struct
        {
            __IO uint32_t r_sdh0_dat3_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat4_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat5_oe_dly_sel: 8;
            __IO uint32_t r_sdh0_dat6_oe_dly_sel: 8;
        } BITS_3AC;
    } u_3AC;

    /* 0x3B0        0x4000_23b0
        7:0     R/W    r_sdh0_dat7_oe_dly_sel          8'h0
        15:8    R/W    RSVD                            8'h0
        23:16   R/W    RSVD                            8'h0
        31:24   R/W    RSVD                            8'h0
    */
    union
    {
        __IO uint32_t REG_SDH0_PHY8;
        struct
        {
            __IO uint32_t r_sdh0_dat7_oe_dly_sel: 8;
            __IO uint32_t RESERVED_2: 8;
            __IO uint32_t RESERVED_1: 8;
            __IO uint32_t RESERVED_0: 8;
        } BITS_3B0;
    } u_3B0;

    /* 0x3B4        0x4000_23b4
        31:0    R/W    sdh_dummy_reg_1                 32'h0
    */
    union
    {
        __IO uint32_t SDIO_DUMMY_REG1;
        struct
        {
            __IO uint32_t sdh_dummy_reg_1: 32;
        } BITS_3B4;
    } u_3B4;

    /* 0x3B8        0x4000_23b8
        31:0    R/W    sdh_dummy_reg_2                 32'h0
    */
    union
    {
        __IO uint32_t SDIO_DUMMY_REG2;
        struct
        {
            __IO uint32_t sdh_dummy_reg_2: 32;
        } BITS_3B8;
    } u_3B8;

    /* 0x3BC        0x4000_23bc
        31:0    R/W    sdh_dummy_reg_3                 32'h0
    */
    union
    {
        __IO uint32_t SDIO_DUMMY_REG3;
        struct
        {
            __IO uint32_t sdh_dummy_reg_3: 32;
        } BITS_3BC;
    } u_3BC;

    /* 0x3C0        0x4000_23c0
        31:0    R/W    sdh_dummy_reg_4                 32'h0
    */
    union
    {
        __IO uint32_t SDIO_DUMMY_REG4;
        struct
        {
            __IO uint32_t sdh_dummy_reg_4: 32;
        } BITS_3C0;
    } u_3C0;

} PERI_BLKCTRL_PERI_CLK_TypeDef;

/* reference: RTL87x2G_PERI-ON_20221017_v2.xlsx */
typedef struct
{
    /* 0x700        0x4000_2700
        0       R/W    sport0_func_en          1'h0
        1       R/W    sport0_ck_en            1'h0
        2       R/W    sport1_func_en          1'h0
        3       R/W    sport1_ck_en            1'h0
        4       R/W    RSVD                    1'h0
        5       R/W    RSVD                    1'h0
        6       R/W    RSVD                    1'h0
        7       R/W    RSVD                    1'h0
        8       R/W    audio_func_en           1'h0
        9       R/W    audio_ck_en             1'h0
        10      R/W    r_CLK_EN_SPORT_40M      1'h0
        13:11   R/W    sp0_dsp_clk_sel         3'h0
        14      R/W    RSVD                    1'h0
        17:15   R/W    sp1_dsp_clk_sel         3'h0
        18      R/W    RSVD                    1'h0
        21:19   R/W    RSVD                    3'h0
        22      R/W    RSVD                    1'h0
        25:23   R/W    RSVD                    3'h0
        26      R/W    RSVD                    1'h0
        27      R/W    RSVD                    1'h0
        28      R/W    r_sport_pll2_ck_en      1'h0
        31:29   R/W    RSVD                    3'h0
    */
    union
    {
        __IO uint32_t REG_SOC_AUDIO_IF_EN;
        struct
        {
            __IO uint32_t sport0_func_en: 1;
            __IO uint32_t sport0_ck_en: 1;
            __IO uint32_t sport1_func_en: 1;
            __IO uint32_t sport1_ck_en: 1;
            __IO uint32_t RESERVED_11: 1;
            __IO uint32_t RESERVED_10: 1;
            __IO uint32_t RESERVED_9: 1;
            __IO uint32_t RESERVED_8: 1;
            __IO uint32_t audio_func_en: 1;
            __IO uint32_t audio_ck_en: 1;
            __IO uint32_t r_CLK_EN_SPORT_40M: 1;
            __IO uint32_t sp0_dsp_clk_sel: 3;
            __IO uint32_t RESERVED_7: 1;
            __IO uint32_t sp1_dsp_clk_sel: 3;
            __IO uint32_t RESERVED_6: 1;
            __IO uint32_t RESERVED_5: 3;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 3;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t r_sport_pll2_ck_en: 1;
            __IO uint32_t RESERVED_0: 3;
        } BITS_700;
    } u_700;

    /* 0x704        0x4000_2704
        7:0     R/W    r_PLL_DIV0_SETTING      8'h0
        15:8    R/W    r_PLL_DIV1_SETTING      8'h0
        23:16   R/W    RSVD                    8'h0
        31:24   R/W    RSVD                    8'h0
    */
    union
    {
        __IO uint32_t REG_AUDIO_PERI_CTL0;
        struct
        {
            __IO uint32_t r_PLL_DIV0_SETTING: 8;
            __IO uint32_t r_PLL_DIV1_SETTING: 8;
            __IO uint32_t RESERVED_1: 8;
            __IO uint32_t RESERVED_0: 8;
        } BITS_704;
    } u_704;

    /* 0x708        0x4000_2708
        0       R/W    r_CODEC_i2s0_master_sel 1'h0
        1       R/W    r_CODEC_i2s1_master_sel 1'h0
        2       R/W    RSVD                    1'h0
        3       R/W    RSVD                    1'h0
        4       R/W    r_SPORT0_EXT_CODEC      1'h0
        5       R/W    r_SPORT1_EXT_CODEC      1'h0
        6       R/W    RSVD                    1'h0
        7       R/W    RSVD                    1'h0
        8       R/W    r_SPORT0_MCLK_OUT       1'h0
        9       R/W    r_SPORT1_MCLK_OUT       1'h0
        10      R/W    RSVD                    1'h0
        11      R/W    RSVD                    1'h0
        31:12   R/W    RSVD                    20'h0
    */
    union
    {
        __IO uint32_t REG_AUDIO_PERI_CTL1;
        struct
        {
            __IO uint32_t r_CODEC_i2s0_master_sel: 1;
            __IO uint32_t r_CODEC_i2s1_master_sel: 1;
            __IO uint32_t RESERVED_6: 1;
            __IO uint32_t RESERVED_5: 1;
            __IO uint32_t r_SPORT0_EXT_CODEC: 1;
            __IO uint32_t r_SPORT1_EXT_CODEC: 1;
            __IO uint32_t RESERVED_4: 1;
            __IO uint32_t RESERVED_3: 1;
            __IO uint32_t r_SPORT0_MCLK_OUT: 1;
            __IO uint32_t r_SPORT1_MCLK_OUT: 1;
            __IO uint32_t RESERVED_2: 1;
            __IO uint32_t RESERVED_1: 1;
            __IO uint32_t RESERVED_0: 20;
        } BITS_708;
    } u_708;

    /* 0x70C        0x4000_270c
        0       R/W    mclk2_en                1'h0
        1       R/W    mclk2_out_sel           1'h0
        3:2     R/W    RSVD                    2'h0
        4       R/W    mclk2_src_sel_0         2'h0
        5       R/W    mclk2_src_sel_1         2'h0
        7:6     R/W    RSVD                    2'h0
        15:8    R/W    mclk2_div_setting       8'h0
        16      R/W    mclk2_pmux_sel          1'h0
        31:17   R/W    RSVD                    15'h0
    */
    union
    {
        __IO uint32_t REG_AUDIO_PERI_CTL2;
        struct
        {
            __IO uint32_t mclk2_en: 1;
            __IO uint32_t mclk2_out_sel: 1;
            __IO uint32_t RESERVED_2: 2;
            __IO uint32_t mclk2_src_sel_0: 1;
            __IO uint32_t mclk2_src_sel_1: 1;
            __IO uint32_t RESERVED_1: 2;
            __IO uint32_t mclk2_div_setting: 8;
            __IO uint32_t mclk2_pmux_sel: 1;
            __IO uint32_t RESERVED_0: 15;
        } BITS_70C;
    } u_70C;

} PERIBLKCTRL_AUDIO_TypeDef;

#define PERIBLKCTRL_PERICLK_REG_BASE0      0x40002300UL
#define PERIBLKCTRL_AUDIO_REG_BASE         0x40002700UL


#define PERIBLKCTRL_PERI_CLK            ((PERI_BLKCTRL_PERI_CLK_TypeDef *) PERIBLKCTRL_PERICLK_REG_BASE0)
#define PERIBLKCTRL_AUDIO               ((PERIBLKCTRL_AUDIO_TypeDef *) PERIBLKCTRL_AUDIO_REG_BASE)

#endif //#define PCC_REG_H
