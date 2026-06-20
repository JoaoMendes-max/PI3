/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "ameba_soc.h"

/**
  * @brief  warm reset the system
  * @param  None
  * @retval None
  */
void System_Reset(void)
{
	WDG_Reset();
}
