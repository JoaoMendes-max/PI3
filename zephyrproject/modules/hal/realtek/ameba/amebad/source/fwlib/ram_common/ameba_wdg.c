/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ameba_soc.h"

/**
  * @brief  Get WDG dividor parameters based on Period
  * @param  Period: WDG timeout (ms).
  * @param  pCountProcess: count id of WDG.
  *         This parameter can be set: 0 ~ 11, represent count value: 0x001~0xFFF
  * @note	The relationship between count id and count: Count = ((0x00000001 << (CountId+1))-1)
  * @param  pDivFacProcess: clock divisor of WDG timeout count.
  * @note	Minimum dividing factor is 1
  * @note	The formula to calculate dividing factor: DivFactor = (u16)(( TimeoutMs * 100)/(Count * 3))
  * @retval None
  */
void WDG_Scalar(u32 Period, u32 *pCountProcess, u32 *pDivFacProcess)
{
	u8 CountId;
	u16 DivFactor;
	u32 CountTemp;
	u32 PeriodProcess = 100 * Period;
	u32 MinPeriodTemp = 0xFFFFFFFF;
	u32 PeriodTemp = 0;

	for (CountId = 0; CountId < 12; CountId++) {
		CountTemp = ((0x00000001 << (CountId + 1)) - 1);
		DivFactor = (u16)((PeriodProcess) / (CountTemp * 3));

		if (DivFactor > 0) {
			PeriodTemp = 3 * (DivFactor + 1) * CountTemp;
			if (PeriodProcess < PeriodTemp) {
				if (MinPeriodTemp > PeriodTemp) {
					MinPeriodTemp = PeriodTemp;
					*pCountProcess = CountId;
					*pDivFacProcess = DivFactor;
				}
			}
		}
	}
}

/**
  * @brief  Initialize the  WDG registers according to the specified parameters
  *         get from WDG_Scalar.
  * @param  WDG_InitStruct: pointer to a WDG_InitTypeDef structure that contains
  *         the configuration information for the WDG peripheral.
  * @retval None
  */
void WDG_Init(WDG_TypeDef *WDG, WDG_InitTypeDef *WDG_InitStruct)
{
	u32 wdg_reg = 0;
	u32 temp = 0;

	wdg_reg = WDG_InitStruct->DivFacProcess & 0xFFFF; /* WdgScalar */
	wdg_reg &= ~(0x00FF0000); /* WdgEnByte */
	wdg_reg |= (WDG_InitStruct->CountProcess & 0xF) << 25;
	wdg_reg |= WDG_BIT_CLEAR;
	wdg_reg |= WDG_BIT_RST_MODE; /* RESET_MODE */
	wdg_reg |= WDG_BIT_ISR_CLEAR; /*Clear ISR*/

	WDG->VENDOR = wdg_reg;

	temp = HAL_READ32(SYSTEM_CTRL_BASE_LP, REG_LP_KM0_CTRL);
	if (WDG_InitStruct->RstAllPERI == 0) {
		temp &= ~BIT_LSYS_WDT_RESET_HS_ALL;
	} else {
		temp |= BIT_LSYS_WDT_RESET_HS_ALL;
	}
	HAL_WRITE32(SYSTEM_CTRL_BASE_LP, REG_LP_KM0_CTRL, temp);
}

/**
  * @brief  Clear WDG interrupt when WDG init use WDG_IrqInit .
  * @param  None
  * @note   This function only used in interrupt mode
  * @retval None
  */
void WDG_IrqClear(void)
{
	WDG_TypeDef *WDG = ((WDG_TypeDef *) WDG_REG_BASE);
	u32 temp = WDG->VENDOR;

	/* Clear ISR */
	temp |= WDG_BIT_ISR_CLEAR;
	WDG->VENDOR = temp;
}

/**
  * @brief  Clear WDG interrupt.
  * @param  WDG: WDG peripheral base.
  * @param  INTrBit specifies the interrupt sources to be cleared
  * @note
  * 	- For compatibility with Zephyr.
  * @retval None
  */
void WDG_ClearINT(WDG_TypeDef *WDG, u32 INTrBit)
{
	UNUSED(INTrBit);
	u32 temp = WDG->VENDOR;

	/* Clear ISR */
	temp |= WDG_BIT_ISR_CLEAR;
	WDG->VENDOR = temp;

	/*WDG reset system*/
	WDG_Reset();
}

/**
  * @brief  Use wdg to reset system in 5ms.
  * @note
  * 	- For compatibility with Zephyr.
  * @retval None
  */
void WDG_Reset(void)
{
	WDG_InitTypeDef WDG_InitStruct;
	WDG_TypeDef *WDG = ((WDG_TypeDef *) WDG_REG_BASE);
	u32 CountProcess;
	u32 DivFacProcess;

	RTK_LOGI(NOTAG, "Rebooting ...\n\r");
	WDG_Scalar(5, &CountProcess, &DivFacProcess);
	WDG_InitStruct.CountProcess = CountProcess;
	WDG_InitStruct.DivFacProcess = DivFacProcess;
	WDG_Init(WDG, &WDG_InitStruct);
	WDG_Cmd(WDG, ENABLE);
}




/**
  * @brief  Init WDG as interrupt mode (close reset mode).
  * @param  handler: WDG interrupt handler
  * @param  Id: WDG interrupt handler parameter
  * @retval None
  */
void WDG_IrqInit(void *handler, u32 Id)
{
	WDG_TypeDef *WDG = ((WDG_TypeDef *) WDG_REG_BASE);
	u32 temp = WDG->VENDOR;

	InterruptRegister((IRQ_FUN)handler, WDG_IRQ, Id, 0);
	InterruptEn(WDG_IRQ, 0);

	temp |= WDG_BIT_ISR_CLEAR;
	temp &= ~WDG_BIT_RST_MODE; /* INT_MODE */
	WDG->VENDOR = temp;
}

/**
  * @brief  This function is meaningless, only for compatibility with Zephyr.
  */
void WDG_INTConfig(WDG_TypeDef *WDG, u32 WDG_IT, u32 NewState)
{
	UNUSED(WDG);
	UNUSED(WDG_IT);
	UNUSED(NewState);
}

/**
  * @brief  Disable/Enable WDG
  * @param  WDG: WDG peripheral base.
  * @param  NewState: new state of the WDG.
  *          This parameter can be: ENABLE or DISABLE
  * @note   To enable WDG timer, set 0x1 to WDG register Bit[16]
  * @retval None
  */
void WDG_Cmd(WDG_TypeDef *WDG, u32 NewState)
{
	u32 temp = WDG->VENDOR;

	/* WdgEnBit */
	if (NewState == ENABLE) {
		temp |= WDG_BIT_ENABLE;
	} else {
		temp &= ~WDG_BIT_ENABLE;
	}

	WDG->VENDOR = temp;

	WDG_IrqClear();
}

/**
  * @brief  Enable WDG
  * @param  WDG: WDG peripheral base.
  * @note
  * 	- For compatibility with Zephyr.
  * @retval None
  */
void WDG_Enable(WDG_TypeDef *WDG)
{
	u32 temp = WDG->VENDOR;

	temp |= WDG_BIT_ISR_CLEAR;
	/* INT_MODE */
	temp &= ~WDG_BIT_RST_MODE;
	/* WdgEnBit */
	temp |= WDG_BIT_ENABLE;
	WDG->VENDOR = temp;

	WDG_IrqClear();
}

/**
  * @brief  Clear WDG timer
  * @param  None
  * @note   If call this function to refresh WDG before timeout period,
  *			then MCU reset or WDG interrupt won't generate
  * @retval None
  */
void WDG_Refresh(WDG_TypeDef *WDG)
{
//	WDG_TypeDef *WDG = ((WDG_TypeDef *) WDG_REG_BASE);
	u32 temp = WDG->VENDOR;

	temp |= WDG_BIT_CLEAR;
	WDG->VENDOR = temp;
}

/**
  * @brief  Set the structure according to the parameters passed in.
  * @param  WDG_InitStruct: pointer to a WDG_InitTypeDef structure that contains
  *         the configuration information for the WDG peripheral.
  * @param  timeout: WDG timeout (ms).
  * @param  window: unused param.
  * @param  eicnt:  unused param.
  * @note
  * 	- For compatibility with Zephyr.
  * @retval None
  */
void WDG_StructMemValueSet(WDG_InitTypeDef *WDG_InitStruct, u32 window, u32 timeout, u32 eicnt)
{
	UNUSED(eicnt);
	UNUSED(window);
	WDG_InitStruct->RstAllPERI = 0;
	WDG_Scalar(timeout, &WDG_InitStruct->CountProcess, &WDG_InitStruct->DivFacProcess);
}
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
