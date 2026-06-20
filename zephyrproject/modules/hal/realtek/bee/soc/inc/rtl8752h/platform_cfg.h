/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _PLATFORM_CFG_H
#define _PLATFORM_CFG_H

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @struct EFUSE_PLATFORM_CONFIG_
 * @brief Platform EFuse settings.
 *
 * Refer to EFUSE[0x].
 */
typedef struct EFUSE_PLATFORM_CONFIG_
{
    uint64_t trace_mask[4];              /* need to be put to first to avoid alignment access fault */

    uint16_t stack_en : 1;
    uint16_t cpu_sleep_en: 1;            /* default = 0 */
    uint16_t run_in_app : 1;             /* boot runs in app */
    uint16_t ftl_init_in_rom : 1;
    uint16_t rsvd0 : 12;

    uint32_t logPin : 6;                 /* default = P0_3 */
    uint32_t logChannel : 2;             /* LogChannel_TypeDef: default is LOG_CHANNEL_LOG1_UART */
    uint32_t logBaudRate : 5;            /* UartBaudRate_TypeDef: default is BAUD_RATE_2000000 */
    uint32_t enableROMMPU : 1;           /* protect rom as Read-only region, default = 1 */
    uint32_t logThreshold : 3;           /* Log threshold: default = 3 (256 = 1 << (5 + 3) */
    uint32_t logDisable : 1;             /* Disable all DBG_DIRECT and DBG_BUFFER log */

    /* rsvd more */
} __attribute__((packed)) SYS_INIT_CONFIG;

extern SYS_INIT_CONFIG sys_init_cfg;

#endif /* _PLATFORM_CFG_H */
