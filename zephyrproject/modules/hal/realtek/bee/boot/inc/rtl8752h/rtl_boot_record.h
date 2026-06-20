/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *                      Define to prevent recursive inclusion
 *============================================================================*/
#ifndef _RTL_BOOT_RECORD_H_
#define _RTL_BOOT_RECORD_H_

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                      Headers
 *============================================================================*/

enum STAGE_INDEXES{
	START_PLATFORM_INIT = 1,
	/* alway execution */
	AON_BOOT_DONE = 2,
	/* post execution */
	PON_BOOT_DONE = 3,
};

/*============================================================================*
 *                      Functions
 *============================================================================*/
void rtl_boot_stage_record(uint8_t index);

#ifdef __cplusplus
}
#endif

#endif /* _RTL_BOOT_RECORD_H_ */
