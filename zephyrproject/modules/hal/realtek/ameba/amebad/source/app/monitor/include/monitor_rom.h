/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _MONITOR_LIB_H_
#define _MONITOR_LIB_H_

_LONG_CALL_ extern u32 cmd_dump_word(u16 argc, u8  *argv[]);
_LONG_CALL_ extern u32 cmd_write_word(u16 argc, u8  *argv[]);
_LONG_CALL_ extern u32 cmd_flash(u16 argc,  u8  *argv[]);
_LONG_CALL_ extern u32 cmd_efuse(u16 argc, u8  *argv[]);
_LONG_CALL_ u32 cmd_rom_table(void **PTable);
#endif
