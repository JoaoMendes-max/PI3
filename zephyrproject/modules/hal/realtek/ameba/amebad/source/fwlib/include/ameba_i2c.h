/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_I2C_H_
#define _AMEBA_I2C_H_

/** @addtogroup AmebaD_Periph_Driver
  * @{
  */

/** @addtogroup I2C I2C
  * @{
  */

/** @addtogroup I2C
  * @verbatim
  *****************************************************************************************
  * Introduction
  *****************************************************************************************
  * I2C0:
  *		- Base Address: I2C0_DEV
  *		- IPclk: 62.5Mhz
  *		- Speed: Standard (up to 100 kHz) and Fast (up to 400 kHz) Modes
  *		- Address: 7/10-bit Address Mode
  *		- SocPs: SleepMode (clock gating & power gating)
  *		- Slave: Slave0
  *		- IRQ: I2C0_IRQ
  *		- GDMA TX handshake interface: GDMA_HANDSHAKE_INTERFACE_I2C0_TX
  *		- GDMA RX handshake interface: GDMA_HANDSHAKE_INTERFACE_I2C0_RX
  *
  *****************************************************************************************
  * How to use Normal I2C
  *****************************************************************************************
  *      To use the normal i2c mode, the following steps are mandatory:
  *
  *      1. Enable peripheral clock using the follwoing functions.(it is enabled by default)
  *			RCC_PeriphClockCmd(APBPeriph_I2Cx, APBPeriph_I2Cx_CLOCK, ENABLE);
  *
  *      2. configure the I2C pinmux.
  *			Pinmux_Config(Pin_Num, PINMUX_FUNCTION_I2C)
  *
  *      3. Program Role, Address Mode, Speed Mode, I2C CLK, Slave address, Threshold, Feature Supports
  *			I2C_StructInit()
  *
  *      4. Init Hardware use step3 parameters:
  *			I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef* I2C_InitStruct)
  *
  *      5. Enable the NVIC and the corresponding interrupt using following function if you need
  *			to use interrupt mode.
  *			I2C_INTConfig(): I2C IRQ Mask set
  *			InterruptRegister(): register the i2c irq handler
  *			InterruptEn(): Enable the NVIC interrupt
  *
  *      6. Enable i2c module using I2C_Cmd().
  *
  *****************************************************************************************
  * How to use i2c in DMA Register mode
  *****************************************************************************************
  *      To use the i2c in DMA mode, the following steps are mandatory:
  *
  *      1. Enable peripheral clock using the follwoing functions.(it is enabled by default)
  *			RCC_PeriphClockCmd(APBPeriph_I2Cx, APBPeriph_I2Cx_CLOCK, ENABLE);
  *
  *      2. configure the I2C pinmux.
  *			Pinmux_Config(Pin_Num, PINMUX_FUNCTION_I2C)
  *
  *      3. Program Role, Address Mode, Speed Mode, I2C CLK, Slave address, Threshold, Feature Supports
  *			I2C_StructInit()
  *
  *      4. Init Hardware use step3 parameters:
  *			I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef* I2C_InitStruct)
  *
  *      5. Enable i2c module using I2C_Cmd().
  *
  *      6. GDMA related configurations(source address/destination address/block size etc.)
  *			I2C_TXGDMA_Init():Init and Enable I2C TX GDMA
  *			I2C_RXGDMA_Init():Init and Enable I2C RX GDMA
  *
  *      7. I2C DMA Mode Register mode set.
  *			I2C_DmaMode1Config():Configures the I2Cx Control Register DMA mode
  *
  *      8. Active the I2C TX/RX DMA Request using I2C_DMAControl().
  *
  *****************************************************************************************
  * How to use i2c in Sleep mode
  *****************************************************************************************
  *      To use the i2c in Low Power mode, the following steps are mandatory:
  *
  *      1. Enable peripheral clock using the follwoing functions.(it is enabled by default)
  *			RCC_PeriphClockCmd(APBPeriph_I2Cx, APBPeriph_I2Cx_CLOCK, ENABLE);
  *
  *      2. configure the I2C pinmux.
  *			Pinmux_Config(Pin_Num, PINMUX_FUNCTION_I2C)
  *
  *      3. Program Role, Address Mode, Speed Mode, I2C CLK, Slave address, Threshold, Feature Supports
  *			I2C_StructInit()
  *
  *      4. Init Hardware use step3 parameters:
  *			I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef* I2C_InitStruct)
  *
  *      5. Enable the NVIC and the corresponding interrupt using following function if you need
  *			to use interrupt mode.
  *			I2C_INTConfig(): I2C IRQ Mask set
  *			InterruptRegister(): register the i2c irq handler
  *			InterruptEn(): Enable the NVIC interrupt
  *
  *      6. Enable address matching interrupts for wake up
  *			I2C_INTConfig(): I2C Addr match IRQ Mask set
  *			BIT_IC_INTR_MASK_M_ADDR_1_MATCH refer to refer to I2C Slave0 Address Match
  *
  *      7. Set wake up event using the follwoing functions.
  *			SOCPS_SetWakeEvent()
  *
  *      8. Set power ext option BIT_SYSON_PMOPT_SLP_ANACK_EN to Enable ANA clock and
  *			BIT_SYSON_PMOPT_SLP_ANACK_SEL to select 4M clock for power save mode, then hardware
  *			will automatically switch to the 4M clock when enter sleep state.
  *			SOCPS_PWROptionExt()
  *
  *      9. Clear address matching interrupts after address matching interrupts
  *			I2C_WakeUp()
  *
  *****************************************************************************************
  * @endverbatim
  */

/* Exported types --------------------------------------------------------*/
/** @defgroup I2C_Exported_Types I2C Exported Types
  * @{
  */

/**
  * @brief  I2C Init structure definition
  */
typedef struct {
	u32	I2CIdx;         /*!< Specifies the I2C Device Index.
				This parameter should be 0 */

	u32	I2CMaster;      /*!< Specifies the I2C Role.
				This parameter can be a value of @ref I2C_Role_definitions */

	u32	I2CAddrMod;     /*!< Specifies the I2C Addressing Mode.
				This parameter can be a value of @ref I2C_Addr_Mode_definitions */

	u32	I2CSpdMod;      /*!< Specifies the I2C Speed Mode. Now the circuit don't support High Speed Mode.
				This parameter can be a value of @ref I2C_Speed_Mode_definitions */

	u32	I2CRXTL;        /*!< Specifies the I2C RX FIFO Threshold. It controls the level of
				entries(or above) that triggers the RX_FULL interrupt.
				This parameter must be set to a value in the 0-255 range. A value of 0 sets
				the threshold for 1 entry, and a value of 255 sets the threshold for 256 entry*/

	u32	I2CTXTL;        /*!< Specifies the I2C TX FIFO Threshold.It controls the level of
				entries(or below) that triggers the TX_EMPTY interrupt.
				This parameter must be set to a value in the 0-255 range. A value of 0 sets
				the threshold for 0 entry, and a value of 255 sets the threshold for 255 entry*/
	u32	I2CMstReSTR;    /*!< Specifies the I2C Restart Support of Master. */

	u32	I2CMstGC;       /*!< Specifies the I2C General Call Support of Master. */

	u32	I2CMstStartB;   /*!< Specifies the I2C Start Byte Support of Master. */

	u32	I2CSlvNoAck;    /*!< Specifies the I2C Slave No Ack Support. */

	u32	I2CSlvAckGC;    /*!< Specifies the I2C Slave Acks to General Call. */

	u32	I2CAckAddr;     /*!< Specifies the I2C Target Address in I2C Master Mode or
				Ack Address in I2C Slave0 Mode.
				This parameter must be set to a value in the 0-127 range if the I2C_ADDR_7BIT
				is selected or 0-1023 range if the I2C_ADDR_10BIT is selected. */

	u32	I2CSlvSetup;       /*!< Specifies the I2C SDA Setup Time. It controls the amount of time delay
				introduced in the rising edge of SCL��relative to SDA changing��by holding SCL low
				when I2C Device operating as a slave transmitter, in units of ic_clk period.
				This parameter must be set to a value in the 0-255 range. It must be set larger than I2CSdaHd */

	u32	I2CSdaHd;       /*!< Specifies the I2C SDA Hold Time. It controls the amount of
				hold time on the SDA signal after a negative edge of SCL in both master
				and slave mode, in units of ic_clk period.
				This parameter must be set to a value in the 0-0xFFFF range. */

	u32	I2CClk;         /*!< Specifies the I2C Bus Clock (in kHz). It is closely related to I2CSpdMod */

	u32	I2CIPClk;		/*!< Specifies the I2C IP Clock (in Hz). */

	u32	I2CFilter;      /*!< Specifies the I2C SCL/SDA Spike Filter. */

	u32	I2CTxDMARqLv;   /*!< Specifies the I2C TX DMA Empty Level. dma_tx_req signal is generated when
				the number of valid data entries in the transmit FIFO is equal to or below the DMA
				Transmit Data Level Register. The value of DMA Transmit Data Level Register is equal
				to this value. This parameter must be set to a value in the 0-31 range. */

	u32	I2CRxDMARqLv;   /*!< Specifies the I2C RX DMA Full Level. dma_rx_req signal is generated when
				the number of valid data entries in the transmit FIFO is equal to or above the DMA
				Receive Data Level Register. The value of DMA Receive Data Level Register is equal to
				this value+1. This parameter must be set to a value in the 0-31 range. */

	u32	I2CDMAMod;     	/*!< Specifies the I2C DMA Mode.
				This parameter can be a value of @ref I2C_DMA_Mode_definitions */

	u32	I2CAckAddr1;    /*!< Specifies the I2C Ack Address in I2C Slave1 Mode. I2C Slave1 only
				support I2C_ADDR_7BIT mode. This parameter must be set to a value in the 0-127 range. */
} I2C_InitTypeDef;
/**
  * @}
  */

/**
  * @brief  I2C Intrerrupt Mode Structure Definition
  */
typedef struct {
	void (*I2CSendSem)(u32 IsWrite);    /*!< Interface for releasing semaphores */
	void (*I2CWaitSem)(u32 IsWrite);    /*!< Interface for acquiring semaphores */
	I2C_TypeDef *I2Cx;
} I2C_IntModeCtrl;

/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup I2C_Exported_Constants I2C Exported Constants
  * @{
  */

/** @defgroup I2C_Peripheral_definitions
  * @{
  */
#define IS_I2C_ALL_PERIPH(PERIPH) ((PERIPH) == I2C0_DEV)
/**
  * @}
  */

/** @defgroup I2C_Addr_Mode_definitions
  * @{
  */
#define I2C_ADDR_7BIT			((u32)0x00000000)
#define I2C_ADDR_10BIT			((u32)0x00000001)
#define IS_I2C_ADDR_MODE(MODE) (((MODE) == I2C_ADDR_7BIT) || \
                                   ((MODE) == I2C_ADDR_10BIT))
/**
  * @}
  */

/** @defgroup I2C_Speed_Mode_definitions
  * @{
  */
#define I2C_SS_MODE				((u32)0x00000001)
#define I2C_FS_MODE				((u32)0x00000002)
#define I2C_HS_MODE				((u32)0x00000003)
#define IS_I2C_SPEED_MODE(MODE) (((MODE) == I2C_SS_MODE) || \
                                   ((MODE) == I2C_FS_MODE) || \
                                   ((MODE) == I2C_HS_MODE))
/**
  * @}
  */

/** @defgroup I2C_Role_definitions
  * @{
  */
#define I2C_SLAVE_MODE			((u32)0x00000000)
#define I2C_MASTER_MODE		((u32)0x00000001)
/**
  * @}
  */

/** @defgroup I2C_DMA_Mode_definitions
  * @{
  */
#define I2C_DMA_LEGACY			((u32)0x00000000)
#define I2C_DMA_REGISTER		((u32)0x00000001)
#define I2C_DMA_DESCRIPTOR		((u32)0x00000002)
#define IS_I2C_DMA_MODE(MODE) (((MODE) == I2C_DMA_LEGACY) || \
                                   ((MODE) == I2C_DMA_REGISTER) || \
                                   ((MODE) == I2C_DMA_DESCRIPTOR))
/**
  * @}
  */

/** @defgroup I2C_DMA_DATA_LENGTH
  * @{
  */
#define IS_I2C_DMA_DATA_LEN(LENGTH)   ((LENGTH) <= 0xFFFF)
/**
  * @}
  */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @defgroup I2C_Exported_Functions I2C Exported Functions
  * @{
  */

/** @defgroup I2C_Exported_Normal_Functions I2C Exported Normal Functions
  * @{
  */
_LONG_CALL_ void I2C_Init(I2C_TypeDef *I2Cx, I2C_InitTypeDef *I2C_InitStruct);
_LONG_CALL_ void I2C_Cmd(I2C_TypeDef *I2Cx, u8 NewState);
_LONG_CALL_ void I2C_ClearAllINT(I2C_TypeDef *I2Cx);
_LONG_CALL_ u32 I2C_GetRawINT(I2C_TypeDef *I2Cx);
_LONG_CALL_ u32 I2C_GetINT(I2C_TypeDef *I2Cx);
_LONG_CALL_ u8 I2C_CheckFlagState(I2C_TypeDef *I2Cx, u32 I2C_FLAG);
_LONG_CALL_ void I2C_INTConfig(I2C_TypeDef *I2Cx, u32 I2C_IT, u32 NewState);
_LONG_CALL_ u32 I2C_ClearINT(I2C_TypeDef *I2Cx, u32 INTrAddr);
_LONG_CALL_ void I2C_SetSpeed(I2C_TypeDef *I2Cx, u32 SpdMd, u32 I2Clk, u32 I2CIPClk);
_LONG_CALL_ void I2C_StructInit(I2C_InitTypeDef *I2C_InitStruct);
_LONG_CALL_ u8 I2C_ReceiveData(I2C_TypeDef *I2Cx);
_LONG_CALL_ s32 I2C_PollFlagRawINT(I2C_TypeDef *I2Cx, u32 I2C_FLAG, u32 I2C_RawINT, u32 timeout_ms);
/**
  * @}
  */

/** @defgroup I2C_Exported_Master_Functions I2C Exported Master Functions
  * @{
  */
_LONG_CALL_ void I2C_MasterSendNullData(I2C_TypeDef *I2Cx, u8 *pBuf, u8  I2CCmd, u8  I2CStop, u8  I2CReSTR);
_LONG_CALL_ void I2C_MasterSend(I2C_TypeDef *I2Cx, u8 *pBuf, u8  I2CCmd, u8  I2CStop, u8  I2CReSTR);
_LONG_CALL_ u32 I2C_MasterWrite(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_MasterReadDW(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_MasterRead(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_MasterRepeatRead(I2C_TypeDef *I2Cx, u8 *pWriteBuf, u32 Writelen, u8 *pReadBuf, u32 Readlen);
_LONG_CALL_ void I2C_SetSlaveAddress(I2C_TypeDef *I2Cx, u16 Address);
_LONG_CALL_ u32 I2C_MasterWriteInt(I2C_TypeDef *I2Cx, I2C_IntModeCtrl *I2C_SemStruct, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_MasterReadInt(I2C_TypeDef *I2Cx, I2C_IntModeCtrl *I2C_SemStruct, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_ISRHandle(I2C_IntModeCtrl *I2C_SemStruct);
_LONG_CALL_ u32 I2C_MasterRead_TimeOut(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len, u32 ms);
_LONG_CALL_ u32 I2C_MasterWrite_TimeOut(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len, u32 ms);
_LONG_CALL_ s32 I2C_MasterSendNullData_TimeOut(I2C_TypeDef *I2Cx, int address, u32 timeout_ms);
/**
  * @}
  */

/** @defgroup I2C_Exported_Slave_Functions I2C Exported Slave Functions
  * @{
  */
_LONG_CALL_ u32 I2C_SlaveWrite(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len);
_LONG_CALL_ u32 I2C_SlaveRead(I2C_TypeDef *I2Cx, u8 *pBuf, u32 len);
_LONG_CALL_ void I2C_SlaveSend(I2C_TypeDef *I2Cx, u8 Data);
/**
  * @}
  */

/** @defgroup I2C_Exported_DMA_Functions I2C Exported DMA Functions
  * @{
  */
_LONG_CALL_ void I2C_DMAControl(I2C_TypeDef *I2Cx, u32 DmaCtrl, u8 NewState);
_LONG_CALL_ void I2C_DmaMode1Config(I2C_TypeDef *I2Cx, u32 I2C_DmaCmd, u32 I2C_DmaBLen);
_LONG_CALL_ void I2C_DmaMode2Config(I2C_TypeDef *I2Cx, u32 I2C_DmaCmd, u32 I2C_DmaBLen);
_LONG_CALL_ bool I2C_TXGDMA_Init(u8 Index, GDMA_InitTypeDef *GDMA_InitStruct, void *CallbackData, IRQ_FUN CallbackFunc, u8 *pTxBuf, int TxCount);
_LONG_CALL_ bool I2C_RXGDMA_Init(u8 Index, GDMA_InitTypeDef *GDMA_InitStruct, void *CallbackData, IRQ_FUN CallbackFunc, u8 *pRxBuf, int RxCount);
/**
  * @}
  */

/** @defgroup I2C_Exported_PowerSave_Functions I2C Exported PowerSave Functions
  * @{
  */
_LONG_CALL_ void I2C_Sleep_Cmd(I2C_TypeDef *I2Cx, u32 NewStatus);
_LONG_CALL_ void I2C_WakeUp(I2C_TypeDef *I2Cx);
/**
  * @}
  */

/**
  * @}
  */


/* Registers Definitions --------------------------------------------------------*/
/**************************************************************************//**
 * @defgroup I2C_Register_Definitions I2C Register Definitions
 * @{
 *****************************************************************************/

/**************************************************************************//**
 * @defgroup IC_CON
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_CON_IC_SLAVE_DISABLE_1		((u32)0x00000001 << 7)
#define BIT_CTRL_IC_CON_IC_SLAVE_DISABLE			((u32)0x00000001 << 6)
#define I2C_BIT_IC_RESTATRT_EN				        ((u32)0x00000001 << 5)
#define BIT_CTRL_IC_CON_IC_10BITADDR_SLAVE		((u32)0x00000001 << 3)
#define BIT_CTRL_IC_CON_SPEED						      ((u32)0x00000003 << 1)
#define I2C_BIT_MASTER_MODE				            ((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_TAR
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_TAR_IC_10BITADDR_MASTER		((u32)0x00000001 << 12)
#define BIT_CTRL_IC_TAR_SPECIAL					      ((u32)0x00000001 << 11)
#define BIT_CTRL_IC_TAR_GC_OR_START				    ((u32)0x00000001 << 10)
#define BIT_CTRL_IC_TAR								        ((u32)0x000003ff)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SAR
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_SAR								((u32)0x000003ff)
/** @} */

/**************************************************************************//**
 * @defgroup IC_DATA_CMD
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_DATA_CMD_NULLDATA				((u32)0x00000001 << 11)
#define BIT_CTRL_IC_DATA_CMD_RESTART				((u32)0x00000001 << 10)
#define BIT_CTRL_IC_DATA_CMD_STOP					  ((u32)0x00000001 << 9)
#define BIT_CTRL_IC_DATA_CMD_CMD					  ((u32)0x00000001 << 8)
#define BIT_CTRL_IC_DATA_CMD_DAT					  ((u32)0x000000ff)
/** @} */

/**************************************************************************//**
 * @defgroup IC_INTR_STAT
 * @{
 *****************************************************************************/
#define BIT_IC_INTR_STAT_R_DMA_I2C_DONE			((u32)0x00000001 << 15)
#define I2C_BIT_R_LP_WAKE_2                 ((u32)0x00000001 << 13) /*!< R 0x0  */
#define I2C_BIT_R_LP_WAKE_1                 ((u32)0x00000001 << 12) /*!< R 0x0  */
#define I2C_BIT_R_GEN_CALL                  ((u32)0x00000001 << 11) /*!< R 0x0  */
#define I2C_BIT_R_START_DET                 ((u32)0x00000001 << 10) /*!< R 0x0  */
#define I2C_BIT_R_STOP_DET                  ((u32)0x00000001 << 9)  /*!< R 0x0  */
#define I2C_BIT_R_ACTIVITY                  ((u32)0x00000001 << 8)  /*!< R 0x0  */
#define I2C_BIT_R_RX_DONE                   ((u32)0x00000001 << 7)  /*!< R 0x0  */
#define I2C_BIT_R_TX_ABRT                   ((u32)0x00000001 << 6)  /*!< R 0x0  */
#define I2C_BIT_R_RD_REQ                    ((u32)0x00000001 << 5)  /*!< R 0x0  */
#define I2C_BIT_R_TX_EMPTY                  ((u32)0x00000001 << 4)  /*!< R 0x0  */
#define I2C_BIT_R_TX_OVER                   ((u32)0x00000001 << 3)  /*!< R 0x0  */
#define I2C_BIT_R_RX_FULL                   ((u32)0x00000001 << 2)  /*!< R 0x0  */
#define I2C_BIT_R_RX_OVER                   ((u32)0x00000001 << 1)  /*!< R 0x0  */
#define I2C_BIT_R_RX_UNDER                  ((u32)0x00000001 << 0)  /*!< R 0x0  */
/** @} */

/**************************************************************************//**
 * @defgroup IC_INTR_MASK
 * @{
 *****************************************************************************/
#define BIT_IC_INTR_MASK_M_DMA_I2C_DONE			((u32)0x00000001 << 15)
#define I2C_BIT_M_LP_WAKE_2 ((u32)0x00000001 << 13) /*!< R/W 0x0  */
#define I2C_BIT_M_LP_WAKE_1 ((u32)0x00000001 << 12) /*!< R/W 0x0  */
#define I2C_BIT_M_GEN_CALL  ((u32)0x00000001 << 11) /*!< R/W 0x0  */
#define I2C_BIT_M_START_DET ((u32)0x00000001 << 10) /*!< R/W 0x0  */
#define I2C_BIT_M_STOP_DET  ((u32)0x00000001 << 9)  /*!< R/W 0x0  */
#define I2C_BIT_M_ACTIVITY  ((u32)0x00000001 << 8)  /*!< R/W 0x0  */
#define I2C_BIT_M_RX_DONE   ((u32)0x00000001 << 7)  /*!< R/W 0x0  */
#define I2C_BIT_M_TX_ABRT   ((u32)0x00000001 << 6)  /*!< R/W 0x0  */
#define I2C_BIT_M_RD_REQ    ((u32)0x00000001 << 5)  /*!< R/W 0x0  */
#define I2C_BIT_M_TX_EMPTY  ((u32)0x00000001 << 4)  /*!< R/W 0x0  */
#define I2C_BIT_M_TX_OVER   ((u32)0x00000001 << 3)  /*!< R/W 0x0  */
#define I2C_BIT_M_RX_FULL   ((u32)0x00000001 << 2)  /*!< R/W 0x0  */
#define I2C_BIT_M_RX_OVER   ((u32)0x00000001 << 1)  /*!< R/W 0x0  */
#define I2C_BIT_M_RX_UNDER  ((u32)0x00000001 << 0)  /*!< R/W 0x0  */
/** @} */

/**************************************************************************//**
 * @defgroup IC_RAW_INTR_STAT
 * @{
 *****************************************************************************/
#define BIT_IC_RAW_INTR_STAT_DMA_I2C_DONE		((u32)0x00000001 << 15)
#define I2C_BIT_LP_WAKE_2 ((u32)0x00000001 << 13) /*!< R 0x0  Set when  address SAR_2 match with address sending on I2C BUS.*/
#define I2C_BIT_LP_WAKE_1 ((u32)0x00000001 << 12) /*!< R 0x0  Set when  address SAR match with address sending on I2C BUS.*/
#define I2C_BIT_GEN_CALL  ((u32)0x00000001 << 11) /*!< R 0x0  Set only when a General Call address is received and it is acknowledged.*/
#define I2C_BIT_START_DET ((u32)0x00000001 << 10) /*!< R 0x0  Indicates whether a START or RESTART condition has occurred on the I2C interface regardless of whether I2C is operating in slave or master mode.*/
#define I2C_BIT_STOP_DET  ((u32)0x00000001 << 9)  /*!< R 0x0  Indicates whether a STOP condition has occurred on the I2C interface regardless of whether I2C is operating in slave or master mode.*/
#define I2C_BIT_ACTIVITY  ((u32)0x00000001 << 8)  /*!< R 0x0  This bit captures I2C activity.*/
#define I2C_BIT_RX_DONE   ((u32)0x00000001 << 7)  /*!< R 0x0  When the I2C is acting as a slave-transmitter, this bit is set to 1 if the master does not acknowledge a transmitted byte. This occurs on the last byte of the transmission, indicating that the transmission is done.*/
#define I2C_BIT_TX_ABRT   ((u32)0x00000001 << 6)  /*!< R 0x0  This bit indicates if I2C as a transmitter, is unable to complete the intended actions on the contents of the transmit FIFO. This situation can occur both as an I2C master or an I2C slave, and is referred to as a 'transmit abort'. * 1: the IC_TX_ABRT_SOURCE register indicates the reason why the transmit abort take places.*/
#define I2C_BIT_RD_REQ    ((u32)0x00000001 << 5)  /*!< R 0x0  This bit is set to 1 when I2C is acting as a slave and another I2C master is attempting to read data from I2C. The I2C holds the I2C bus in a wait state(SCL=0) until this interrupt is serviced, which means that the slave has been addressed by a remote master that is asking for data to be transferred. The processor must respond to this interrupt and then write the requested data to the IC_DATA_CMD register.*/
#define I2C_BIT_TX_EMPTY  ((u32)0x00000001 << 4)  /*!< R 0x0  This bit is set to 1 when the transmit buffer is at or below the threshold value set in the IC_TX_TL register. It is automatically cleared by hardware when the buffer level goes above the threshold.*/
#define I2C_BIT_TX_OVER   ((u32)0x00000001 << 3)  /*!< R 0x0  Set during transmit if the transmit buffer is filled to IC_TX_BUFFER_DEPTH and the processor attempts to issue another I2C command by writing to the IC_DATA_CMD register.*/
#define I2C_BIT_RX_FULL   ((u32)0x00000001 << 2)  /*!< R 0x0  Set when the receive buffer goes above the RX_TL threshold in the IC_RX_TL register. It is automatically cleared by hardware when buffer level is equal to or less than the threshold.*/
#define I2C_BIT_RX_OVER   ((u32)0x00000001 << 1)  /*!< R 0x0  Not used. Set if the receive buffer is completely filled to IC_RX_BUFFER_DEPTH and an additional byte is received from an external I2C device.*/
#define I2C_BIT_RX_UNDER  ((u32)0x00000001 << 0)  /*!< R 0x0  Set if the processor attempts to read the receive buffer when it is empty by reading from the IC_DATA_CMD register.*/
/** @} */

/**************************************************************************//**
 * @defgroup IC_ENABLE
 * @{
 *****************************************************************************/
#define I2C_BIT_ENABLE							        ((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_STATUS
 * @{
 *****************************************************************************/
#define BIT_IC_STATUS_SLV_ACTIVITY            ((u32)0x00000001 << 6)
#define BIT_IC_STATUS_MST_ACTIVITY            ((u32)0x00000001 << 5)
#define I2C_BIT_RFF                     			((u32)0x00000001 << 4)
#define I2C_BIT_RFNE                   				((u32)0x00000001 << 3)
#define I2C_BIT_TFE                     			((u32)0x00000001 << 2)
#define I2C_BIT_TFNF                    			((u32)0x00000001 << 1)
#define BIT_IC_STATUS_ACTIVITY                ((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SDA_HOLD
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_SDA_HOLD						((u32)0x0000ffff)
/** @} */

/**************************************************************************//**
 * @defgroup IC_TX_ABRT_SOURCE
 * @{
 *****************************************************************************/
#define BIT_IC_TX_ABRT_SOURCE_ABRT_SLVRD_INTX 		((u32)0x00000001 << 15)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_SLV_ARBLOST		((u32)0x00000001 << 14)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_SLVFLUSH_TXFIFO	((u32)0x00000001 << 13)
#define BIT_IC_TX_ABRT_SOURCE_ARB_LOST        			((u32)0x00000001 << 12)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_MASTER_DIS 		((u32)0x00000001 << 11)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_10B_RD_NORSTRT	((u32)0x00000001 << 10)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_SBYTE_NORSTRT	((u32)0x00000001 << 9)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_HS_NORSTRT 		((u32)0x00000001 << 8)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_SBYTE_ACKDET		((u32)0x00000001 << 7)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_HS_ACKDET		((u32)0x00000001 << 6)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_GCALL_READ 		((u32)0x00000001 << 5)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_GCALL_NOACK		((u32)0x00000001 << 4)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_TXDATA_NOACK	((u32)0x00000001 << 3)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_10ADDR2_NOACK	((u32)0x00000001 << 2)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_10ADDR1_NOACK	((u32)0x00000001 << 1)
#define BIT_IC_TX_ABRT_SOURCE_ABRT_7B_ADDR_NOACK	((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SLV_DATA_NACK_ONLY
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_SLV_DATA_NACK_ONLY				((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_DMA_CR
 * @{
 *****************************************************************************/
#define I2C_BIT_TDMAE                   				((u32)0x00000001 << 1)
#define I2C_BIT_RDMAE                   				((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SDA_SETUP
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_SDA_SETUP              					((u32)0x000000ff)
/** @} */

/**************************************************************************//**
 * @defgroup IC_ACK_GENERAL_CALL
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_ACK_GENERAL_CALL					((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_DMA_CMD
 * @{
 *****************************************************************************/
#define I2C_BIT_DMODE_RESTART ((u32)0x00000001 << 7) /*!< R/W 0x0  This bit controls whether a RESTART is issued after the byte is sent or received in DMA mode. * 1: a RESTART is issued after the data is sent/received (according to the value of CMD_RW), regardless of whether or not the transfer direction is changing from the previous command.*/
#define I2C_BIT_DMODE_STOP    ((u32)0x00000001 << 6) /*!< R/W 0x0  This bit controls whether a STOP is issued after the byte is sent or received in DMA mode. * 1: STOP is issued after this byte, regardless of whether or not the Tx FIFO is empty. If the Tx FIFO is not empty, the master immediately tries to start a new transfer by issuing a START and arbitrating for the bus. * 0: STOP is not issued after this byte.*/
#define I2C_BIT_DMODE_CMD     ((u32)0x00000001 << 5) /*!< R/W 0x0  This bit controls whether a read or write is performed in DMA mode. This bit does not control the direction when the I2C acts as a slave. It controls only the direction when it acts as a master. * 1: Read * 0: Write*/
#define I2C_BIT_DMODE_ENABLE  ((u32)0x00000001 << 0) /*!< WA0 0x0  * 1: Set to enable dma mode, clear when transfer is done*/
/** @} */

/**************************************************************************//**
 * @defgroup IC_DMA_MOD
 * @{
 *****************************************************************************/
#define BIT_IC_DMA_MOD									((u32)0x00000003)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SLEEP
 * @{
 *****************************************************************************/
#define BIT_IC_SLEEP_CLOCK_GATED						((u32)0x00000001 << 1)
#define BIT_IC_SLEEP_CLOCK_CONTROL					((u32)0x00000001)
/** @} */

/**************************************************************************//**
 * @defgroup IC_FILTER
 * @{
 *****************************************************************************/
#define BIT_IC_FILTER_DIG_FLTR_SEL						((u32)0x00000001 << 8)
#define BIT_CTRL_IC_FILTER_DIG_FLTR_DEG				((u32)0x0000000F)
/** @} */

/**************************************************************************//**
 * @defgroup IC_SAR1
 * @{
 *****************************************************************************/
#define BIT_CTRL_IC_SAR1								((u32)0x0000007F)
/** @} */
/** @} */

/**
  * @}
  */

/**
  * @}
  */

/* Other Definitions --------------------------------------------------------*/
//I2C Timing Parameters
#define I2C_SS_MIN_SCL_HTIME		4000    //the unit is ns.
#define I2C_SS_MIN_SCL_LTIME		4700    //the unit is ns.

#define I2C_FS_MIN_SCL_HTIME		600     //the unit is ns.
#define I2C_FS_MIN_SCL_LTIME		1300    //the unit is ns.

#define I2C_HS_MIN_SCL_HTIME_100    60      //the unit is ns, with bus loading = 100pf
#define I2C_HS_MIN_SCL_LTIME_100    120     //the unit is ns., with bus loading = 100pf

#define I2C_HS_MIN_SCL_HTIME_400    160     //the unit is ns, with bus loading = 400pf
#define I2C_HS_MIN_SCL_LTIME_400    320     //the unit is ns., with bus loading = 400pf


#define I2C_TRX_BUFFER_DEPTH 16
#define I2C_POLL_TIMEOUT_MS  1000

typedef struct {
	I2C_TypeDef *I2Cx;
	u32 Tx_HandshakeInterface;
	u32 Rx_HandshakeInterface;
	IRQn_Type IrqNum;
} I2C_DevTable;

extern const I2C_DevTable I2C_DEV_TABLE[1];
extern u32 I2C_SLAVEWRITE_PATCH;
extern u32 IC_FS_SCL_HCNT_TRIM;
extern u32 IC_FS_SCL_LCNT_TRIM;

#endif

/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
