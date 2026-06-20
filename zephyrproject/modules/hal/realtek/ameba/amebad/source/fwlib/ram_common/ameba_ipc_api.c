/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ameba_soc.h"

/**
  * @brief  init ipc channel according to ipc_init_config[].
  * @param  where IPCx can be IPCKM0_DEV for KM0, IPCKM4_DEV for CM4.
  * @retval   None
  */
void ipc_table_init(IPC_TypeDef *IPCx)
{
	u32 i;
	(void) IPCx;

	for (i = 0;;) {
		/*  Check if search to end */
		if (ipc_init_config[i].USER_MSG_TYPE == 0xFFFFFFFF) {
			break;
		}

		if ((ipc_init_config[i].func != NULL) || (ipc_init_config[i].IrqData != NULL)) {
			IPC_INTUserHandler(i, (void *)ipc_init_config[i].func, ipc_init_config[i].IrqData);
		}

		i++;
	}
}
u32 Messages[32] = {0};
/**
  * @brief  exchange messages between KM0 and KM4.
  * @param  IPC_Dir: nonuse
  * @param  IPC_ChNum: the IPC channel number.
   * @param  IPC_Msg: pointer to the message to be exchanged,and should not stored in stack.
  * @retval   None
  */
u32 ipc_send_message(u32 IPC_Dir, u8 IPC_ChNum, PIPC_MSG_STRUCT IPC_Msg)
{
	u32 CpuId = IPC_CPUID();
	IPC_TypeDef *IPC_DEV;
	(void) IPC_Dir;

	if (CpuId == KM4_CPU_ID) {
		IPC_DEV = IPCM4_DEV;
	} else {
		IPC_DEV = IPCM0_DEV;
	}

#ifndef __ZEPHYR__
	extern uint32_t *vTaskStackAddr(void);
	extern uint32_t vTaskStackSize(void);

	if (IPC_USER_POINT == ipc_init_config[IPC_ChNum].USER_MSG_TYPE) {
		/*message is shared between two cpu ,so it can't store in stack
		 * assume stack down growth, and 0x100 is an estimated value
		 */
		assert_param((IPC_Msg->msg > (u32)(vTaskStackAddr() + vTaskStackSize() * 4)) || (IPC_Msg->msg < (u32)vTaskStackAddr()));
	}
#endif

	if ((IPC_ChNum > 10) && (IPC_ChNum < 32)) {
		Messages[IPC_ChNum] = (u32)IPC_Msg->msg;
		IPC_DEV->IPCx_USR[11] = (u32)&Messages[0];
	} else {
		IPC_DEV->IPCx_USR[IPC_ChNum] = (u32)IPC_Msg->msg;
	}

	IPC_INTRequest(IPC_DEV, IPC_ChNum);

	return IPC_SEND_SUCCESS;
}

/**
  * @brief  get ipc message.
  * @param  IPC_Dir: nonuse
  * @param  IPC_ChNum: the IPC channel number.
  * @retval  : pointer to the message to be exchanged.
  * @note for data massage, corresponding data cache should be invalidate before access.
  */
IPC_MSG_STRUCT ipc_msg_temp;
PIPC_MSG_STRUCT ipc_get_message(u32 IPC_Dir, u8 IPC_ChNum)
{
	(void) IPC_Dir;
	PIPC_MSG_STRUCT IPC_Msg = &ipc_msg_temp;
	u32 CpuId = IPC_CPUID();
	IPC_TypeDef *IPC_DEV;

	/*KM4 read mesaage for km0*/
	if (CpuId == KM4_CPU_ID) {
		IPC_DEV = IPCM0_DEV;
	} else {
		IPC_DEV = IPCM4_DEV;
	}

	if (IPC_ChNum > 10) {
		u32 *Messages_address = (u32 *)IPC_DEV->IPCx_USR[11];
		DCache_Invalidate((u32) &Messages_address[IPC_ChNum], sizeof(u32));
		IPC_Msg->msg = Messages_address[IPC_ChNum];
	} else {
		IPC_Msg->msg = IPC_DEV->IPCx_USR[IPC_ChNum];
	}

	return (PIPC_MSG_STRUCT)IPC_Msg;
}
/******************* (C) COPYRIGHT 2016 Realtek Semiconductor *****END OF FILE****/
