/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _IMAGE_CHECK_H_
#define _IMAGE_CHECK_H_
#include <stdbool.h>
#include <stdint.h>
#include <image_info.h>

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

typedef struct _ROM_HEADER_FORMAT
{
    uint8_t uuid[UUID_SIZE];
    void *init_ptr;
    void *entry_ptr;
} T_ROM_HEADER_FORMAT;

/*************************************************************************************************
*                          functions
*************************************************************************************************/
IMG_CHECK_ERR_TYPE image_entry(uint16_t image_id, uint32_t image_addr);

IMG_CHECK_ERR_TYPE image_entry_check(T_ROM_HEADER_FORMAT *rom_header,
                                     T_ROM_HEADER_FORMAT *patch_header);

#endif // _IMAGE_CHECK_H_
