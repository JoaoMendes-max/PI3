/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _SECTION_CONFIG_H_
#define _SECTION_CONFIG_H_

#include "basic_types.h"

#define RAM_VECTOR_TABLE1_SECTION	SECTION(".ram_vector_table1")
#define RAM_VECTOR_TABLE2_SECTION	SECTION(".ram_vector_table2")
#define RAM_VECTOR_TABLE3_SECTION	SECTION(".ram_vector_table3")

//3 Hal Section
#define HAL_ROM_ENTRY_NS_SECTION	SECTION(".hal.rom.entryns.rodata")
#define SIM_ROM_DATA_SECTION		SECTION(".sim.rom.rodata")
//#define HAL_ROM_TEXT_SECTION		SECTION(".hal.rom.text")
//#define HAL_ROM_DATA_SECTION		SECTION(".hal.rom.rodata")
//#define HAL_ROM_BSS_SECTION			SECTION(".hal.rom.bss")
#define HAL_ROM_BSS_SECTION_BANK	SECTION(".hal.rom.bank.bss")

//3 Apple  Section
#define APPLE_ROM_TEXT_SECTION		SECTION(".apple.rom.text")
#define APPLE_ROM_DATA_SECTION		SECTION(".apple.rom.rodata")

//3 Libc Section
#define LIBC_ROM_TEXT_SECTION		SECTION(".libc.rom.text")

//3 Shell
#define SHELL_ROM_TEXT_SECTION		HAL_ROM_TEXT_SECTION
#define SHELL_ROM_BSS_SECTION		HAL_ROM_BSS_SECTION
#define SHELL_ROM_DATA_SECTION		HAL_ROM_DATA_SECTION

#define BOOT_RAM_TEXT_SECTION		SECTION(".boot.ram.text")

#define GIT_VER_TABLE_SECTION		SECTION(".git.ver.data")
#define IPC_TABLE_DATA_SECTION		SECTION(".ipc.table.data")
#define CMD_TABLE_DATA_SECTION		SECTION(".cmd.table.data")

//3 Image 1 data
#define IMAGE1_ENTRY_SECTION		SECTION(".image1.entry.data")
#define IMAGE1_EXPORT_SYMB_SECTION	SECTION(".image1.export.symb")
#define IMAGE1_VALID_PATTEN_SECTION	SECTION(".image1.validate.rodata")
#define IMAGE2_VALID_PATTEN_SECTION	SECTION(".image2.validate.rodata")

//3 SRAM Config Section
#define SRAM_NOCACHE_DATA_SECTION	SECTION(".nocache.data")
#define IMAGE2_ENTRY_SECTION		SECTION(".image2.entry.data")
#define IMAGE2_RAM_TEXT_SECTION		SECTION(".image2.ram.text")


#if defined (CONFIG_ARM_CORE_CM4)
#define PSRAM_TEXT_SECTION			SECTION(".psram.text")
#define PSRAM_DATA_SECTION			SECTION(".psram.data")
#define PSRAM_BSS_SECTION			SECTION(".psram.bss")
#endif

//3 SSL Section
#define SSL_RAM_MAP_SECTION			SECTION(".ssl_ram_map")

#define RETENTION_TEXT_SECTION		SECTION(".retention.ram.text")
#define RETENTION_DATA_SECTION		SECTION(".retention.ram.data")
#define RETENTION_ENTRY_SECTION		SECTION(".retention.entry.data")

/* image3 secure image */
#define IMAGE3_ENTRY_SECTION		SECTION(".image3.nsc_entry.text")

#define TIMESENSITIVE_TEXT_SECTION	SECTION(".timesensitive.text")
#define TIMESENSITIVE_DATA_SECTION	SECTION(".timesensitive.data")

/* non.dram can put in Flash(No DeepPowerDown) or SRAM after psram disabled, such as pmc code */
#define NON_DRAM_TEXT_SECTION				SECTION(".non.dram.text")

/* .sramdram.only means cannot put in Flash, such as flash api */
#define SRAMDRAM_ONLY_TEXT_SECTION			SECTION(".sramdram.only.text")

/* .sramdram.only means cannot put in Flash, such as flash api */
#define SRAM_ONLY_TEXT_SECTION				SECTION(".sram.only.text")
#define SRAM_ONLY_DATA_SECTION				SECTION(".sram.only.data")

#define SRAM_WLAN_CRITICAL_CODE_SECTION

// Wlan Section(Not Used)
#define CONFIG_FW_CRITICAL_CODE_SECTION		//IMAGE2_RAM_TEXT_SECTION
#define WLAN_ROM_TEXT_SECTION
#define WLAN_ROM_DATA_SECTION
#define WLAN_RAM_MAP_SECTION
#define WLAN_ROM_BSS_SECTION
//for KM4 compile original rom code
#define HAL_ROM_BSS_SECTION
#define HAL_ROM_TEXT_SECTION
#define HAL_ROM_DATA_SECTION

#endif //_SECTION_CONFIG_H_
