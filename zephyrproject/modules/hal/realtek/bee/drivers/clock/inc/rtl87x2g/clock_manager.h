/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _CLOCK_MANAGER_H_
#define _CLOCK_MANAGER_H_

#include <stdint.h>
#include <stdbool.h>

/* ======================== Active clock func declaration ========================== */
extern void (*set_active_mode_clk_src)(void);
extern void (*set_lp_module_clk_info)(void);
extern void (*set_up_32k_clk_src)(void);
void init_osc_sdm_timer(void);
/* ==================== End of Active clock func declaration ===============================*/

#endif
