/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/**************************************************************************//**
 * @file     mac_port_macro.h
 * @brief    Header file for MAC/PHY driver platform porting macros.
 *
 * @version  V1.00
 * @date     2022-09-14
 *
 * @note
 *
 ******************************************************************************/

#ifndef _MAC_DRIVER_PORT_H_
#define _MAC_DRIVER_PORT_H_

/* define macros for MAC driver porting on the specified platform here */
#include "rtl876x.h"                           /*!< ARM Cortex-M4 processor and core peripherals                              */

#define PORT_CATEGORY_BT_SOC
#define PORT_PLATFORM_RTL87X2G

#define DEFAULT_RF_MODE     RF_TPM
#ifndef _IS_ASIC_   // FPGA, use external RF board
#undef DEFAULT_RF_MODE
#define DEFAULT_RF_MODE     RF_IQM
#endif

#endif  /* end of _MAC_DRIVER_PORT_H_ */
