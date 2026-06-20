/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_DIAG_H_
#define _AMEBA_DIAG_H_

/** @addtogroup AmebaD_Platform
  * @{
  */

/** @defgroup DIAG
  * @brief DIAG driver modules
  * @{
  */

/** @addtogroup DIAG
  * @verbatim
  *****************************************************************************************
  * Introduction
  *****************************************************************************************
  *		-Control API for LOGUART.
  *		-These API is used by system, user should not use these API if not needed.
  *		-LOGUART is UART2.
  *
  *****************************************************************************************
  * pinmux
  *****************************************************************************************
  *		-S0: GPIOA_16/17: QFN48, QFN68, QFN48-MCM.
  *		-S1: GPIOA_29/30: QFN32.
  *		-EFUSE 0x19[6]: 0: S1 PA29 & PA30, 1: S0 PA16 & PA17.
  *
  *****************************************************************************************
  * @endverbatim
  */

/* Exported constants --------------------------------------------------------*/

/** @defgroup DIAG_Exported_Constants DIAG Exported Constants
  * @{
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DIAG_Exported_Functions DIAG Exported Functions
  * @{
  */
_LONG_CALL_ void LOGUART_DiagInit(bool InitConsol);

_LONG_CALL_ void LOGUART_PutChar(u8 c);
_LONG_CALL_ u8 LOGUART_GetChar(bool    PullMode);
_LONG_CALL_ u8 LOGUART_Readable(void);
_LONG_CALL_ u32 LOGUART_GetIMR(void);
_LONG_CALL_ void LOGUART_SetIMR(u32 SetValue);
_LONG_CALL_ void LOGUART_WaitBusy(void);
_LONG_CALL_ int LOGUART_SetBaud(u32 BaudRate);
_LONG_CALL_ u32 LOGUART_Writable(void);
_LONG_CALL_ u32 LOGUART_GetStatus(UART_TypeDef *UARTLOG);
_LONG_CALL_ void LOGUART_INTClear(UART_TypeDef *UARTLOG, u32 UART_IT);
_LONG_CALL_ void LOGUART_INTConfig(UART_TypeDef *UARTLOG, u32 UART_IT, u32 newState);

#define DiagPutChar		LOGUART_PutChar
#define DiagGetChar		LOGUART_GetChar

/* UART line status bit */
#define LOGUART_BIT_TIMEOUT_INT       RUART_BIT_TIMEOUT_INT
#define LOGUART_BIT_TP1F_EMPTY        RUART_BIT_TX_EMPTY
#define LOGUART_BIT_DRDY              RUART_BIT_DRDY
#define LOGUART_BIT_RXFIFO_INT        RUART_BIT_RXFIFO_INT

/* UART interrupt clear bit */
#define LOGUART_BIT_TOICF             RUART_BIT_TOICF /* Used to clear rx timeout int in Dplus */

/* UART interrupt enable bit */
#define LOGUART_BIT_ERBI              RUART_BIT_ERBI
#define LOGUART_BIT_ETOI              RUART_BIT_ETOI
#define LOGUART_BIT_ELSI              RUART_BIT_ELSI
#define LOGUART_TX_EMPTY_PATH_1_INTR  RUART_BIT_ETBEI

#define LOGUART_DEV			((UART_TypeDef		*) UART2_DEV)

#ifdef __ZEPHYR__
#define LOGUART_RxCmd(UARTLOG, NewState) (void)0;
#define LOGUART_INT_NP2AP() (void)0;
#endif
/**
  * @}
  */


/**
  * @}
  */

/**
  * @}
  */

/* Other definations --------------------------------------------------------*/

#endif //_AMEBA_DIAG_H_
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
