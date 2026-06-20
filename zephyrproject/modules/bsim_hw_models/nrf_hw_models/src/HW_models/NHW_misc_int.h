/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef NHW_MISC_INT_H
#define NHW_MISC_INT_H

#include <string.h>
#include <bs_types.h>
#include <bs_oswrap.h>
#include "NHW_config.h"
#include "NHW_peri_types.h"

#define DEF_ENTRY(peri, suf) \
    {(void *)NRF_##peri##suf##_BASE,  NRF_##peri##suf##_BASE_REAL_HW, sizeof(NRF_##peri##_Type)}

struct simu_real_conv_table_t {
  void* simu_addr;
  uint32_t real_add;
  uint32_t size;
};

uint nhw_get_simu_real_conv_table(struct simu_real_conv_table_t **table);

#endif /* NHW_MISC_INT_H */
