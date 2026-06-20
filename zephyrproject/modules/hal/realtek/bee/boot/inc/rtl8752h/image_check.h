/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _IMAGE_CHECK_H_
#define _IMAGE_CHECK_H_

#include <stdbool.h>
#include <stdint.h>
#include <image_header.h>

/*============================================================================*
  *                                   Types
  *============================================================================*/

typedef enum
{
    IMG_CHECK_PASS,
    IMG_CHECK_ERR_HEADER_ADDR,
    IMG_CHECK_ERR_NOT_READY,
    IMG_CHECK_ERR_ROM_UUID,
    IMG_CHECK_ERR_MAGIC_PATTERN,
    IMG_CHECK_ERR_SIZE,
    IMG_CHECK_ERR_ID,
    IMG_CHECK_ERR_ENTRY_RETURN,
    IMG_CHECK_ERR_VERIFY,
    IMG_CHECK_ERR_EXE_BASE,
    IMG_CHECK_ERR_IC_TYPE,
    IMG_CHECK_ERR_MAX,
} IMG_CHECK_ERR_TYPE;

/*============================================================================*
  *                                   Functions
 *============================================================================*/

/**
 * @brief  Check the validity of the specified image
 *
 * @param[in]  image_id Specify the image
 * @param[in]  header_addr Specify image header address
 *
 * @return Check result
 * @retval IMG_CHECK_PASS If image check passes
 * @retval fail Otherwise
*/
extern IMG_CHECK_ERR_TYPE check_header_valid(uint32_t header_addr, T_IMG_ID image_id);

extern IMG_CHECK_ERR_TYPE image_entry_check(T_ROM_HEADER_FORMAT *rom_header,
                                            T_ROM_HEADER_FORMAT *patch_header);

#endif /* _IMAGE_CHECK_H_ */
