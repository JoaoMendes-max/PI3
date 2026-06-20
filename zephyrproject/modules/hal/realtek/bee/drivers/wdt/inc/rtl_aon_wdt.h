/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *               Define to prevent recursive inclusion
 *============================================================================*/
#ifndef RTL_AON_WDT_H
#define RTL_AON_WDT_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                               Header Files
*============================================================================*/
#include "utils/rtl_utils.h"
#include "wdt/inc/rtl_wdt.h"
#if defined (CONFIG_SOC_SERIES_RTL87X2G)
#include "wdt/src/rtl87x2g/rtl_aon_wdt_def.h"
#endif

/** \defgroup AON_WDT         AON_WDT
  * \brief
  * \{
  */

/*============================================================================*
 *                         Functions
 *============================================================================*/
/** \defgroup AON_WDT_Exported_Functions AON_WDT Exported Functions
  * \{
  */

/**
 * \brief  Start AON WDT.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration.
 * \param[in] TimeMs    AON WDT Timeout Time. Unit: ms.
 * \param[in] Mode      Refer to \ref WDTMode_TypeDef. If the Reset AON WDT operation is not performed within the Timeout period,
 *                       the configured mode operation will be executed.
 *
 * \return  true or false.
 *          - true: AON WDT mode set successfully, enabling the function..
 *          - false: If set to interrupt mode, it will return false.
 */
bool AON_WDT_Start(AON_WDT_TypeDef *AON_WDTx, uint32_t TimeMs, WDTMode_TypeDef Mode);

/**
 * \brief  Disable AON WDT.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration.
 */
void AON_WDT_Disable(AON_WDT_TypeDef *AON_WDTx);

/**
 * \brief  Kick AON WDT to restart WDT.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration
 */
void AON_WDT_Kick(AON_WDT_TypeDef *AON_WDTx);

/**
 * \brief  Is AON WDT enable.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration.
 *
 * \return Is AON WDT enable or not
 */
bool AON_WDT_IsEnable(AON_WDT_TypeDef *AON_WDTx);

/**
 * \brief  Get AON WDT timeout.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration.
 *
 * \return AON WDT timeout
 */
uint32_t AON_WDT_GetTimeoutMs(AON_WDT_TypeDef *AON_WDTx);

/**
 * \brief  Get AON WDT mode.
 *
 * \param[in] AON_WDTx  Select the AON_WDT peripheral. Refer to \ref AON_WDT_Declaration.
 *
 * \return AON WDT mode
 */
WDTMode_TypeDef AON_WDT_GetMode(AON_WDT_TypeDef *AON_WDTx);

/** End of AON_WDT_Exported_Functions
  * \}
  */

/** End of AON_WDT
  * \}
  */

#ifdef __cplusplus
}
#endif

#endif /* RTL_AON_WDT_H */
