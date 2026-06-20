/*
 * Copyright (c) 2019 Oticon A/S
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "nrfx.h"
#include "bs_tracing.h"

#define PERIPHERAL_REG_BASE(per, nbr, post) \
    (void*)NRF_##per##nbr##post##_BASE

#define IS_PERIPHERAL_REG(p, per, nbr, post) \
    (p >= PERIPHERAL_REG_BASE(per, nbr, post)) && \
    ((uintptr_t)p < (uintptr_t)PERIPHERAL_REG_BASE(per, nbr, post) + sizeof(NRF_##per##_Type))

#define NOT_KNOWN_PER_ERROR \
  bs_trace_error_time_line("Tried to get the peripheral number of an address unknown to these HW models\n")
