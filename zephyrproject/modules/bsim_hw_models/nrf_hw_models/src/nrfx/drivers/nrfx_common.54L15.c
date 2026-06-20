/*
 * Copyright (c) 2019 Oticon A/S
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "nrfx_common_int.h"

IRQn_Type nrfx_get_irq_number(void const * p_reg) {
  /* 28..63 :not real */
  if (IS_PERIPHERAL_REG(p_reg, SPU, 00, _S)) {
    return SPU00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, MPC, 00, _S)) {
    return MPC00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, AAR, 00, _S)) {
    return AAR00_CCM00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, CCM, 00, _S)) {
    return AAR00_CCM00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, ECB, 00, _S)) {
    return ECB00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, CRACEN, , _S)) {
    return CRACEN_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 00, _S)) {
    return SERIAL00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RRAMC, , _S)) {
    return RRAMC_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, VPR, 00, _S)) {
    return VPR00_IRQn;
  /* CTRLAP */
  /* CM33S */
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 00, _S)) {
    return TIMER00_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SPU, 10, _S)) {
    return SPU10_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 10, _S)) {
    return TIMER10_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 10, _S)) {
    return EGU10_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RADIO, , _S)) {
    return RADIO_0_IRQn;
    /* Note RADIO has 2 interrupts */
  } else if (IS_PERIPHERAL_REG(p_reg, SPU, 20, _S)) {
    return SPU20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 20, _S)) {
    return SERIAL20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 21, _S)) {
    return SERIAL21_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 22, _S)) {
    return SERIAL22_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 20, _S)) {
    return EGU20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 20, _S)) {
    return TIMER20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 21, _S)) {
    return TIMER21_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 22, _S)) {
    return TIMER22_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 23, _S)) {
    return TIMER23_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 24, _S)) {
    return TIMER24_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, PDM, 20, _S)) {
    return PDM20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, PDM, 21, _S)) {
    return PDM21_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, PWM, 20, _S)) {
    return PWM20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, PWM, 21, _S)) {
    return PWM21_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, PWM, 22, _S)) {
    return PWM22_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SAADC, , _S)) {
    return SAADC_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, NFCT, , _S)) {
    return NFCT_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TEMP, , _S)) {
    return TEMP_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, GPIOTE, 20, _S)) {
    return GPIOTE20_0_IRQn;
    /* Note GPIO20 has two interrupts */
  } else if (IS_PERIPHERAL_REG(p_reg, TAMPC, , _S)) {
    return TAMPC_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, I2S, 20, _S)) {
    return I2S20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, QDEC, 20, _S)) {
    return QDEC20_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, QDEC, 21, _S)) {
    return QDEC21_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, GRTC, , _S)) {
    return GRTC_0_IRQn;
    /* Note GRTC has 4 interrupts */
  } else if (IS_PERIPHERAL_REG(p_reg, SPU, 30, _S)) {
    return SPU30_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 30, _S)) {
    return SERIAL30_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, COMP, , _S)) {
    return COMP_LPCOMP_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, WDT, 30, _S)) {
    return WDT30_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, WDT, 31, _S)) {
    return WDT31_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, GPIOTE, 30, _S)) {
    return GPIOTE30_0_IRQn;
    /* Note GPIO20 has two interrupts */
  } else if (IS_PERIPHERAL_REG(p_reg, CLOCK, , _S)) {
    return CLOCK_POWER_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, POWER, , _S)) {
    return CLOCK_POWER_IRQn;
  } else {
    NOT_KNOWN_PER_ERROR;
    return 0; /* unreachable */
  }
}
