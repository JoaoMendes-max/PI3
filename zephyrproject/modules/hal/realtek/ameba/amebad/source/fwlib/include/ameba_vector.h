/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_VECTOR_H_
#define _AMEBA_VECTOR_H_

/** @addtogroup AmebaD_Platform
  * @{
  */

/** @defgroup IRQ
  * @brief IRQ modules
  * @{
  */

/** @addtogroup IRQ
  * @verbatim
  *****************************************************************************************
  * Introduction
  *****************************************************************************************
  * IRQ table, please refer to IRQ Exported Constants->IRQn_enum->IRQn
  *
  *****************************************************************************************
  * how to use
  *****************************************************************************************
  *		1. register/unregister IRQ use: InterruptRegister/InterruptUnRegister
  *		2. enable/disable IRQ use: InterruptEn/InterruptDis
  *
  *****************************************************************************************
  * @endverbatim
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup IRQ_Exported_Types IRQ Exported Types
  * @{
  */
typedef void (*HAL_VECTOR_FUN)(void);
typedef u32(*IRQ_FUN)(void *Data);
/**
  * @}
  */


/* Exported functions --------------------------------------------------------*/
/** @defgroup IRQ_Exported_Functions IRQ Exported Functions
  * @{
  */
extern _LONG_CALL_ void irq_table_init(u32 StackP);
extern _LONG_CALL_ bool irq_register(IRQ_FUN IrqFun, IRQn_Type IrqNum, u32 Data, u32 Priority);
extern _LONG_CALL_ bool irq_unregister(IRQn_Type IrqNum);
extern _LONG_CALL_ void irq_enable(IRQn_Type   IrqNum);
extern _LONG_CALL_ void irq_disable(IRQn_Type   IrqNum);
extern _LONG_CALL_ void irq_clear_pending(IRQn_Type irqn);
extern _LONG_CALL_ void irq_set_priority(IRQn_Type irqn, uint32_t priority);
extern _LONG_CALL_ uint32_t irq_get_priority(IRQn_Type irqn);

#define InterruptRegister			irq_register_check
#define InterruptUnRegister		irq_unregister

#define InterruptEn(a,b)			irq_enable(a)
#define InterruptDis(a)			irq_disable(a)
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/* Other Definitions --------------------------------------------------------*/
extern IRQ_FUN UserIrqFunTable[];
extern u32 UserIrqDataTable[];
extern HAL_VECTOR_FUN  NewVectorTable[];

#if defined (CONFIG_ARM_CORE_CM4)
#define MAX_VECTOR_TABLE_NUM			(64+16)
#define MAX_PERIPHERAL_IRQ_NUM		64
#define MAX_IRQ_PRIORITY_VALUE			7
#define IRQ_PRIORITY_SHIFT				1
#else
#define MAX_VECTOR_TABLE_NUM			(16+32)
#define MAX_PERIPHERAL_IRQ_NUM		32
#define MAX_NVIC_IPR_NUM				((MAX_PERIPHERAL_IRQ_NUM + 3) >> 2)
#define MAX_IRQ_PRIORITY_VALUE			3
#define IRQ_PRIORITY_SHIFT				2
#endif

#define MSP_RAM_LP			0x0008FFFC
#define MSP_RAM_HP			0x1007EFFC
#define MSP_RAM_HP_NS		0x10002FFC

static inline bool irq_register_check(IRQ_FUN IrqFun, IRQn_Type IrqNum, u32 Data,  u32 Priority)
{
	if (Priority > MAX_IRQ_PRIORITY_VALUE) {
		Priority = MAX_IRQ_PRIORITY_VALUE;
	}
	Priority = (Priority << IRQ_PRIORITY_SHIFT);
	return irq_register(IrqFun, IrqNum, Data, Priority);
}

#endif //_AMEBA_VECTOR_H_

