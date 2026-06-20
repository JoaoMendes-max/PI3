/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *                         Define to prevent recursive inclusion
 *============================================================================*/
#ifndef RTL_UTILS_H
#define RTL_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                         Header Files
 *============================================================================*/
#include <stdint.h>
#include <stdbool.h>
#include "bitops.h"
#include "cpu_setting.h"

/*============================================================================*
 *                         Types
*============================================================================*/
/** \defgroup UTILS       UTILS
  * \brief
  * \{
  */

/** \defgroup UTILS_Exported_Constants UTILS Exported Constants
  * \brief
  * \{
  */

/**
 * \defgroup    ITStatus ITStatus
 * \{
 * \ingroup     UTILS_Exported_Constants
 */
typedef enum
{
    RESET = 0,      //!< Define the constant RESET and assign it the value 0.
    SET = !RESET    //!< Define the constant SET and assign it the value 1.
} FlagStatus, ITStatus;

/** End of ITStatus
  * \}
  */

/**
 * \defgroup    FunctionalState FunctionalState
 * \{
 * \ingroup     UTILS_Exported_Constants
 */
typedef enum
{
    DISABLE = 0,         //!< Define the constant DISABLE and assign it the value 0.
    ENABLE = !DISABLE    //!< Define the constant ENABLE and assign it the value 1.
} FunctionalState;

#define IS_FUNCTIONAL_STATE(STATE) (((STATE) == DISABLE) || ((STATE) == ENABLE)) //!< Check if the input parameter is valid.

/** End of FunctionalState
  * \}
  */

/** End of UTILS_Exported_Constants
  * \}
  */

/*============================================================================*
 *                         Functions
 *============================================================================*/
/** \defgroup UTILS_Exported_Functions UTILS Exported Functions
  * \brief
  * \{
  */

/* Uncomment the line below to expanse the "assert_param" macro in the
   Standard Peripheral Library drivers code */
//#define USE_FULL_ASSERT

/**
  * \brief  The assert_param macro is used for function's parameters check.
  * \param  expr: If expr is false, it calls assert_failed function which reports
  *         the name of the source file and the source line number of the call
  *         that failed. If expr is true, it returns no value.
  *
  */
#ifdef USE_FULL_ASSERT
#define assert_param(expr) ((expr) ? (void)0 : io_assert_failed((uint8_t *)__FILE__, __LINE__))
void io_assert_failed(uint8_t *file, uint32_t line);
#else
#define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */

/** End of UTILS_Exported_Functions
  * \}
  */

/** End of UTILS
  * \}
  */
#ifdef __cplusplus
}
#endif

#endif /* RTL_UTILS_H */

