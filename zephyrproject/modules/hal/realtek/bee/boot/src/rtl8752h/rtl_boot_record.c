/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *                        Header Files
 *============================================================================*/
#include <rtl876x.h>
#include <rtl876x_aon_reg.h>
#include <rtl_boot_record.h>

/*============================================================================*
 *                         Types
 *============================================================================*/
enum {
	START_TO_RUN_C_CODE = 3,
	AFTER_CHECK_PAD_BOOT_FROM_FLASH_I = 4,
	AFTER_LOAD_PATCH = 5,
	AFTER_SET_SECURE_REG = 6,
};

/*============================================================================*
 *                          Private Macros
 *============================================================================*/
#define BOOT_STAGE_RECORD(x) btaon_fast_update(AON_FAST_REG_REG0X_FW_GENERAL, 1 << (x), 1 << (x))

/*============================================================================*
 *                           Public Functions
 *============================================================================*/
void rtl_boot_stage_record(uint8_t index)
{
    AON_FAST_REG_REG0X_FW_GENERAL_TYPE aon_fast_reg_0x0 = {};
    switch (index)
    {
    case START_PLATFORM_INIT:
        BOOT_STAGE_RECORD(AFTER_LOAD_PATCH);
        break;
    case AON_BOOT_DONE:
        aon_fast_reg_0x0.d16 = btaon_fast_read(AON_FAST_REG_REG0X_FW_GENERAL);
        aon_fast_reg_0x0.aon_boot_done = 1;
        btaon_fast_write(AON_FAST_REG_REG0X_FW_GENERAL, aon_fast_reg_0x0.d16);
        break;
    case PON_BOOT_DONE:
        aon_fast_reg_0x0.d16 = btaon_fast_read(AON_FAST_REG_REG0X_FW_GENERAL);
        aon_fast_reg_0x0.pon_boot_done = 1;
        btaon_fast_write(AON_FAST_REG_REG0X_FW_GENERAL, aon_fast_reg_0x0.d16);
        break;
    default:
        break;
    }
}

