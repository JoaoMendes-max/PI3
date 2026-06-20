/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef __SYS_RESET_H_
#define __SYS_RESET_H_

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                               Header Files
*============================================================================*/
#include "wdt/inc/rtl_wdt.h"

/*============================================================================*
 *                         Types
 *============================================================================*/
/**
  * @brief       Watch Dog Mode structure definition.
  * @note        Watch Dog Reset reason introduction:
  *              1.If you want to get reset reason from aon 0x15, deviding three types:
  *              a) HW reset: aon reg 0x15 is cleared to 0, magic pattern on ram will change
  *              b) SW RESET_ALL: aon reg 0x15 is cleared to 0,but magic pattern on ram not change
  *              c) SW RESET_ALL_EXCEPT_AON: obtain reset reason by reading aon reg 0x15 .
  *              2. Attention: don't use 0x1 as your reset reason when using RESET_ALL_EXCEPT_AON type! Because 0x1 is default value.
  */
typedef enum
{
    RESET_REASON_HW                         = 0x0,
    RESET_REASON_WDT_TIMEOUT                = 0x1,
    RESET_REASON_BOOT_EFUSE_INVALID         = 0x2,
    RESET_REASON_BOOT_FLASH_INVALID         = 0x3,
    RESET_REASON_BOOT_RETRY_COUNT_LIMIT     = 0x4,
    RESET_REASON_HARD_FAULT                 = 0x5,
    RESET_REASON_FLASH_IOCTL                = 0x6,
    RESET_REASON_LOWER_STACK                = 0x7,
    RESET_REASON_PASSWORD_DEBUG             = 0x8,
    RESET_REASON_ENTER_FT_MODE              = 0x9,
    RESET_REASON_SWITCH_TO_HCI_MODE         = 0xA,
    RESET_REASON_SWITCH_TO_OTA_MODE         = 0xB,
    RESET_REASON_DFU_FW_RESET               = 0xC,
    RESET_REASON_DFU_UPDATE_IMG             = 0xD,
    RESET_REASON_DFU_UPDATE_IMG_FAIL        = 0xE,
    RESET_REASON_DFU_DISCONN_RSP            = 0xF,
    RESET_REASON_DFU_DISCONN_IND            = 0x10,
    RESET_REASON_ROM_DFU_OPCODE_SYSTEM_RESET = 0x11,
    RESET_REASON_DATATRANS_PATCH_ACTIVE     = 0x12,
    RESET_REASON_DATATRANS_SYSTEM_RESET     = 0x13,
    RESET_REASON_MP_RESET                   = 0x14,
    RESET_REASON_FEATURE_CHECK_FAIL         = 0x15,
    RESET_REASON_FLASH_LAYOUT_OVERFLOW      = 0x16,
    RESET_REASON_DFU_UPDATE_COMPRESSED_IMG  = 0x17,
    RESET_REASON_BRANCH_TO_NS_FAIL          = 0x18,
    RESET_REASON_BRANCH_TO_S_FAIL           = 0x19,
    RESET_REASON_DLPS                       = 0x1A,
    RESET_REASON_POWER_DOWN                 = 0x1B,
    RESET_REASON_ZEPHYR                     = 0x1C,
    SW_RESET_APP_END                = 0xFF,
} T_SW_RESET_REASON;

/*============================================================================*
 *                              Functions
*============================================================================*/
/**
 * @brief Execute a system reset via the watchdog.
 * 
 * This function performs a system reboot using the specified watchdog mode
 * `wdt_mode`, and optionally logs the reason for the reset as `reset_reason`.
 * 
 * @param wdt_mode Specifies the watchdog mode for the reset, refer to @ref WDTMode_TypeDef.
 * @param reset_reason Provides the reason for the system reset, useful for further diagnostics and tracking.
 */

extern void WDG_SystemReset(WDTMode_TypeDef wdt_mode, int reset_reason);

/**
 * @brief Retrieve the reason for the system reset.
 * 
 * This function returns the reason for the most recent system reset, useful for diagnosing reboot events.
 * 
 * @param none
 * @return Returns the reason for the system reset, type T_SW_RESET_REASON.
 */

static inline T_SW_RESET_REASON reset_reason_get()
{
    extern T_SW_RESET_REASON sw_reset_reason;
    return sw_reset_reason;
}

#ifdef __cplusplus
}
#endif

#endif /* __SYS_RESET_H_ */
