/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _RTL876X_AON_REG_H
#define _RTL876X_AON_REG_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                      Headers
 *============================================================================*/
#include <stdint.h>

/*============================================================================*
 *                         Macros
 *============================================================================*/
#define AON_FAST_REG_REG0X_FW_GENERAL               0x0

/*============================================================================*
 *                         Types
 *============================================================================*/
/* 0x0
    6:0     R/W freg0[6:0]                              7'h0
    7       W1P reg_rom_trace_prot                      1'h0
    15:8    R   reserved                                8'h0
 */
typedef volatile union _AON_FAST_REG_REG0X_FW_GENERAL_TYPE
{
    uint16_t d16;
    struct
    {
        uint16_t aon_boot_done : 1;
        uint16_t pon_boot_done : 1;
        uint16_t rsvd : 5;
        uint16_t reg_rom_trace_port : 1;
        uint16_t is_disable_set_reg_by_otp: 1;
        uint16_t RESERVED_0: 7;
    };
} AON_FAST_REG_REG0X_FW_GENERAL_TYPE;

#ifdef __cplusplus
}
#endif

#endif /* _RTL876X_AON_REG_H */
