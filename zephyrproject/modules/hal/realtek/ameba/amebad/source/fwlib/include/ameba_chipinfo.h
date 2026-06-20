/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_CHIPINFO_H_
#define _AMEBA_CHIPINFO_H_

#define MEMORY_NOT_CLEAR	0x400000

/** @defgroup CHIPINFO_TypeDef
  * @{
  */
typedef struct {
	u8 sub_num;
	u8 package_num;
	u16 bd_num;
	u32 memory_type;
} CHIPINFO_TypeDef;
/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup HWINFO_Exported_Functions HWINFO Exported Functions
  * @{
  */
_LONG_CALL_ void ChipInfo_GetSocName_ToBuf(char *buf, size_t buflen);
_LONG_CALL_ void ChipInfo_GetLibVersion_ToBuf(char *buf, size_t buflen);
_LONG_CALL_ bool ChipInfo_PsramExists(void);

/**
  * @}
  */

#endif
