/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _HAL_SDIO_HOST_H_
#define _HAL_SDIO_HOST_H_


#include "ameba_sdio_host.h"



#define SDIO_HOST_WAIT_FOREVER       0xFFFFFFFF



typedef struct _HAL_SDIO_HOST_OP_ {
	HAL_Status(*HalSdioHostInitHost)(void *Data);
	HAL_Status(*HalSdioHostInitCard)(void *Data);
	HAL_Status(*HalSdioHostDeInit)(void *Data);
	HAL_Status(*HalSdioHostRegIrq)(void *Data);
	HAL_Status(*HalSdioHostReadBlocksDma)(void *Data, u64 ReadAddr, u32 BlockCnt);
	HAL_Status(*HalSdioHostWriteBlocksDma)(void *Data, u64 WriteAddr, u32 BlockCnt);
	HAL_Status(*HalSdioHostStopTransfer)(void *Data);
	HAL_Status(*HalSdioHostGetCardStatus)(void *Data);
	HAL_Status(*HalSdioHostGetSdStatus)(void *Data);
	HAL_Status(*HalSdioHostChangeSdClock)(void *Data, u8 Frequency);
	HAL_Status(*HalSdioHostErase)(void *Data, u64 StartAddr, u64 EndAddr);
	HAL_Status(*HalSdioHostGetWriteProtect)(void *Data);
	HAL_Status(*HalSdioHostSetWriteProtect)(void *Data, u8 Setting);
} HAL_SDIO_HOST_OP, *PHAL_SDIO_HOST_OP;

typedef struct _HAL_SDIO_HOST_ADAPTER_ {
//	IRQ_HANDLE				IrqHandle;			// Irq Handler
	ADMA2_DESC_FMT			*AdmaDescTbl;
	u32						Response[4];
	u32						CardOCR;
	u32 					CardStatus;
	u32						IsWriteProtect;
	u8 						SdStatus[SD_STATUS_LEN];
	u8						Csd[CSD_REG_LEN];
	volatile u8             CmdCompleteFlg;
	volatile u8             XferCompleteFlg;
	volatile u8             ErrIntFlg;
	volatile u8             CardCurState;
	u8						IsSdhc;
	u8						CurrSdClk;
	u16 					RCA;
	u16						SdSpecVer;
	void (*CardInsertCallBack)(void *pAdapter);
	void (*CardRemoveCallBack)(void *pAdapter);
	void *CardInsertCbPara;
	void *CardRemoveCbPara;
} HAL_SDIO_HOST_ADAPTER, *PHAL_SDIO_HOST_ADAPTER;


extern HAL_Status
HalSdioHostInit(
	void *Data
);

extern HAL_Status
HalSdioHostDeInit(
	void *Data
);

extern HAL_Status
HalSdioHostEnable(
	void *Data
);

extern HAL_Status
HalSdioHostDisable(
	void *Data
);

extern void
HalSdioHostOpInit(
	void *Data
);


#endif

