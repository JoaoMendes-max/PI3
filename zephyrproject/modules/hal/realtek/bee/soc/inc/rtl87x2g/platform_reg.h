/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef PLATFORM_REG_H
#define PLATFORM_REG_H
#include <stdint.h>

/* ================================================================================ */
/* ================                PLATFORM Register               ================ */
/* ===========     Reference: RTL87x2G_Reg_SoC_202201012_v0.xlsx     =========== */
/* ================================================================================ */
typedef struct
{
    /* 0x0000       0x4000_3000
        31:0    R/W    RSVD                            32'h0
    */
    __IO uint32_t RSVD_0000;

    /* 0x0004       0x4000_3004
        0       R/W1C  spic0_intr_r                    1'h0
        1       R/W1C  spic1_intr_r                    1'h0
        2       R/W1C  spic2_intr_r                    1'h0
        3       R/W1C  trng_intr_r                     1'h0
        4       R/W1C  lpcomp_intr_r                   1'h0
        5       R/W1C  spi_phy1_intr_r                 1'h0
        30:6    R      RSVD                            25'h0
        31      R/W1C  utmi_suspend_n_r                1'h0
    */
    union
    {
        __IO uint32_t REG_LOW_PRI_INT_STATUS;
        struct
        {
            __IO uint32_t spic0_intr_r: 1;
            __IO uint32_t spic1_intr_r: 1;
            __IO uint32_t spic2_intr_r: 1;
            __IO uint32_t trng_intr_r: 1;
            __IO uint32_t lpcomp_intr_r: 1;
            __IO uint32_t spi_phy1_intr_r: 1;
            __I uint32_t RESERVED_0: 25;
            __IO uint32_t utmi_suspend_n_r: 1;
        } BITS_004;
    } u_004;

    /* 0x0008       0x4000_3008
        31:0    R/W    low_pri_int_mode                32'hFFFFFFFF
    */
    union
    {
        __IO uint32_t REG_LOW_PRI_INT_MODE;
        struct
        {
            __IO uint32_t low_pri_int_mode: 32;
        } BITS_008;
    } u_008;

    /* 0x000C       0x4000_300c
        31:0    R/W    low_pri_int_en                  32'h0
    */
    union
    {
        __IO uint32_t REG_LOW_PRI_INT_EN;
        struct
        {
            __IO uint32_t low_pri_int_en: 32;
        } BITS_00C;
    } u_00C;

    /* 0x0010       0x4000_3010
        0       R      timer_intr1_intr0_r             1'h0
        1       R      bluewiz_intr_r                  1'h0
        2       R      RSVD                            1'h0
        3       R      bluewiz_dma_intr_r              1'h0
        4       R      pro_intr_r                      1'h0
        31:5    R      RSVD                            27'h0
    */
    union
    {
        __IO uint32_t BT_MAC_INTERRUPT;
        struct
        {
            __I uint32_t timer_intr1_intr0_r: 1;
            __I uint32_t bluewiz_intr_r: 1;
            __I uint32_t RESERVED_1: 1;
            __I uint32_t bluewiz_dma_intr_r: 1;
            __I uint32_t pro_intr_r: 1;
            __I uint32_t RESERVED_0: 27;
        } BITS_010;
    } u_010;

    /* 0x0014       0x4000_3014
        23:0     R       RSVD                                           24'h0
        26:24    R/W     RSVD                                           3'h0
        31:27    R       RSVD                                           5'h0
    */
    union
    {
        __IO uint32_t RXI_INTERRUPT;
        struct
        {
            __I uint32_t RESERVED_0: 32;
        } BITS_014;
    } u_014;

    /* 0x0018       0x4000_3018
        31:0    R/W    low_pri_int_pol                 32'h0
    */
    union
    {
        __IO uint32_t INTERRUPT_EDGE_OPTION;
        struct
        {
            __IO uint32_t low_pri_int_pol: 32;
        } BITS_018;
    } u_018;

} SoC_VENDOR_REG_TypeDef;


#define SOC_VENDOR_REG_BASE             0x40003000UL
#define VENDOR_REG_BASE                 SOC_VENDOR_REG_BASE

#define SoC_VENDOR                      ((SoC_VENDOR_REG_TypeDef    *) SOC_VENDOR_REG_BASE)

#endif //#define PLATFORM_REG_H
