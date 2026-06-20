/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_PMC_H_
#define _AMEBA_PMC_H_

/** @addtogroup AmebaD_Platform
  * @{
  */

/** @defgroup PMC
  * @brief PMC driver modules
  * @{
  */

/** @addtogroup PMC
  * @verbatim
  *****************************************************************************************
  * Introduction
  *****************************************************************************************
  * we support  following soc power save functions:
  *		- sleep clock gating
  *		- sleep power gating
  *		- deep standby
  *		- deep sleep
  *
  *****************************************************************************************
  * sleep power gating
  *****************************************************************************************
  * following functions can be used when power gating:
  *		-UART0/UART1
  *		-TIM4/TIM5
  *		-RTC
  *		-WIFI
  *		-SDIO
  *		-USB
  *		-I2C0/I2C1
  *		-ADC
  *		-GPIO
  *		-REGU timer
  *		-normal wakepin
  *		-ANA timer
  * following functions will be closed when power gating:
  *		-UART2 LOGUART
  *		-TIM0-TIM3
  *		-SPIC flash
  *
  *****************************************************************************************
  * deep standby
  *****************************************************************************************
  * following functions can be used when deep standby:
  *		-RTC
  *		-REGU timer
  *		-normal wakepin
  *		-ANA timer
  *
  *****************************************************************************************
  * deep sleep
  *****************************************************************************************
  * following functions can be used when deep standby:
  *		-REGU timer
  *		-REGU wakepin
  *
  *****************************************************************************************
  * wakepin (A18/A5/A22/A23: mux normal wakepin and REGU wakepin)
  *****************************************************************************************
  * normal wakepin:
  *		-SLP_CG
  *		-SLP_PG
  *		-STDBY
  * REGU wakepin:
  *		-just used in DSLP (1.2V closed)
  *		-just support high acive, so this pin should pull low on your board
  *
  *****************************************************************************************
  *****************************************************************************************
  * SLP & SNZ power option
  *****************************************************************************************
  * BIT_SYSON_PMOPT_SLP_EN_SWR & BIT_SYSON_PMOPT_SNZ_EN_SWR
  *		-we have two 1.2V LDO
  *			-BIG LDO: SWR mode or LDO mode (can config )
  *			-LITTLE LDO: a little 1.2v LDO
  *		-BIT_SYSON_PMOPT_SLP_EN_SWR
  *			-ENABLE/DISABLE BIG LDO when SLP
  *		BIT_SYSON_PMOPT_SNZ_EN_SWR
  *			-ENABLE/DISABLE BIG LDO when SNZ, WIFI & ADC need open BIG LDO when SNZ
  *
  * BIT_SYSON_PMOPT_SLP_EN_PWM & BIT_SYSON_PMOPT_SNZ_EN_PWM
  *		-BIT_SYSON_PMOPT_SLP_EN_PWM
  *			-ENABLE/DISABLE LDO heavy loading current mode when SLP
  *		-BIT_SYSON_PMOPT_SNZ_EN_PWM
  *			-ENABLE/DISABLE heavy loading current mode when SNZ, WIFI & ADC need heavy loading when SNZ
  *
  * BIT_SYSON_PMOPT_SLP_XTAL_EN & BIT_SYSON_PMOPT_SNZ_XTAL_EN
  *		-WIFI and SOC both need XTAL when work,
  *		-but WIFI have individual option to control XTAL, so BIT_SYSON_PMOPT_SNZ_XTAL_EN not needed
  *
  * BIT_SYSON_PMOPT_SLP_SYSPLL_EN & BIT_SYSON_PMOPT_SNZ_SYSPLL_EN
  *		-WIFI and SOC both have individual PLL, here is SOC 500M PLL
  *		-So BIT_SYSON_PMOPT_SNZ_SYSPLL_EN not needed
  *
  * BIT_SYSON_SNFEVT_WIFI_MSK = 1 & BIT_SYSON_BYPASS_SNZ_SLP = 1
  *		- after OS suspend, platform will enter SNZ and close CPU, then platform enter sleep mode when WIFI 32K
  *		- BIT_SYSON_PMOPT_SNZ_EN_SOC should never open, or CPU will not close when platform will enter SNZ
  *
  * BIT_SYSON_SNFEVT_WIFI_MSK = 1 & BIT_SYSON_BYPASS_SNZ_SLP = 0 (not use this config)
  *		- after OS suspend, platform will enter sleep mode & close CPU after WIFI 32K
  *****************************************************************************************
  * @endverbatim
  */


/* Exported constants --------------------------------------------------------*/

/** @defgroup PMC_Exported_Constants PMC Exported Constants
  * @{
  */

/** @defgroup SOCPS_PS_Wakeup_Pin_definitions
  * @{
  */
#define	WAKUP_0							((u32)0x00000000)/*!< see aon_wakepin */
#define	WAKUP_1							((u32)0x00000001)/*!< see aon_wakepin */
#define	WAKUP_2							((u32)0x00000002)/*!< see aon_wakepin */
#define	WAKUP_3							((u32)0x00000003)/*!< see aon_wakepin */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

typedef struct {
	u32 km0_config_wifi_enable;
	u32 km0_enable_key_touch;
	u32 km0_osc2m_close; /* just uart and normal ADC(2M/12=166K) use it, captouch ADC use 131K */
	u32 km0_pg_enable;
	u32 km0_rtc_calibration;
	u32 km0_audio_pad_enable;
	u32 km0_disable_audio_ldo;

	/* debug */
	u32 km0_fw_idle_time;
	u32 km0_clk_down_time;
	u32 km0_rf_off_time;
	u32 km0_gating_time;
	u32 km0_rf_on_time;
	u32 km0_wake_time;
	u32 km0_dur1;
} PSCFG_TypeDef;

extern PSCFG_TypeDef ps_config;

void SOCPS_SetWakeEventAON(u32 Option, u32 NewStatus);
void SOCPS_SleepCG_RAM(void);
void SOCPS_SWR_PFMForce(u32 NewStatus);
int SOCPS_WakeEvent(void);

#endif //_AMEBA_PMC_H_
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
