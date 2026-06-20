/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**************************************************************************//**
 * @file     zb_section.h
 * @brief    define memory section name for zigbee.
 *
 * @version  V1.00
 * @date     2023-05-06
 *
 * @note
 *
 ******************************************************************************/

#ifndef _ZB_SECTION_H_
#define _ZB_SECTION_H_

#if !defined(SECTION)
#define SECTION(_name) __attribute__ ((__section__(_name)))
#endif

#define SECTION_ZB_ROM_TEXT         SECTION(".rom.zb.text")
#define SECTION_ZB_ROM_RODATA       SECTION(".rom.zb.rodata")
#define SECTION_ZB_ROM_DATA         SECTION(".rom.zb.data")
#define SECTION_ZB_ROM_BSS          SECTION(".rom.zb.bss")

#define SECTION_ZB_PATCH_TEXT       SECTION(".patch.zb.text")
#define SECTION_ZB_PATCH_RODATA     SECTION(".patch.zb.rodata")
#define SECTION_ZB_PATCH_DATA       SECTION(".patch.zb.data")
#define SECTION_ZB_PATCH_BSS        SECTION(".patch.zb.bss")

#define SECTION_ZB_MP_ROM_TEXT      SECTION(".rom.zb_mp.text")
#define SECTION_ZB_MP_ROM_RODATA    SECTION(".rom.zb_mp.rodata")
#define SECTION_ZB_MP_ROM_DATA      SECTION(".rom.zb_mp.data")
#define SECTION_ZB_MP_ROM_BSS       SECTION(".rom.zb_mp.bss")

#define SECTION_ZB_MP_PATCH_TEXT    SECTION(".patch.zb_mp.text")
#define SECTION_ZB_MP_PATCH_RODATA  SECTION(".patch.zb_mp.rodata")
#define SECTION_ZB_MP_PATCH_DATA    SECTION(".patch.zb_mp.data")
#define SECTION_ZB_MP_PATCH_BSS     SECTION(".patch.zb_mp.bss")

#define SECTION_ZB_IPC_TEXT         SECTION(".zb_ipc.text")
#define SECTION_ZB_IPC_ITCM         SECTION(".zb_ipc.itcm.text")
#define SECTION_ZB_IPC_RODATA       SECTION(".zb_ipc.rodata")
#define SECTION_ZB_IPC_DATA         SECTION(".zb_ipc.data")
#define SECTION_ZB_IPC_BSS          SECTION(".zb_ipc.bss")
#define SECTION_ZB_IPC_SHARE_MEM    SECTION(".zb_ipc_share.bss")
#define SECTION_ZB_IPC_BUF_DESC     SECTION(".zb_ipc_buf_desc.rodata")

#define SECTION_ZB_PM_ROM_TEXT      SECTION(".rom.zb_pm.text")
#define SECTION_ZB_PM_ROM_RODATA    SECTION(".rom.zb_pm.rodata")
#define SECTION_ZB_PM_ROM_DATA      SECTION(".rom.zb_pm.data")
#define SECTION_ZB_PM_ROM_BSS       SECTION(".rom.zb_pm.bss")

#endif // _ZB_SECTION_H_
