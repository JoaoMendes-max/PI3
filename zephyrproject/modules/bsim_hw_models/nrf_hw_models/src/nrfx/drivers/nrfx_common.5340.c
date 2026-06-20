/*
 * Copyright (c) 2019 Oticon A/S
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 */

#include "nrfx_common_int.h"

IRQn_Type nrfx_get_irq_number(void const * p_reg) {

#if defined(NRF5340_XXAA_NETWORK)

  if (IS_PERIPHERAL_REG(p_reg, POWER,, _NS)) {
    return CLOCK_POWER_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, CLOCK,, _NS)) {
    return CLOCK_POWER_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RADIO,, _NS)) {
    return RADIO_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RNG,, _NS)) {
      return RNG_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, GPIOTE,, _NS)) {
    return GPIOTE_IRQn;
  /* 11 WDT */
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 0, _NS)) {
      return TIMER0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, ECB,, _NS)) {
      return ECB_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, AAR,, _NS)) {
      return AAR_CCM_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, CCM,, _NS)) {
      return AAR_CCM_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TEMP,, _NS)) {
      return TEMP_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RTC, 0, _NS)) {
      return RTC0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, IPC,, _NS)) {
      return IPC_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 0, _NS)) {
      return SERIAL0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 0, _NS)) {
      return EGU0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RTC, 1, _NS)) {
      return RTC1_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 1, _NS)) {
      return TIMER1_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 2, _NS)) {
      return TIMER2_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SWI, 0, _NS)) {
      return SWI0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SWI, 1, _NS)) {
      return SWI1_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SWI, 2, _NS)) {
      return SWI2_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, SWI, 3, _NS)) {
      return SWI3_IRQn;
  }
#elif defined(NRF5340_XXAA_APPLICATION)

  /* 0 FPU */
  /* 1 CACHE */
  /* 3 SPU */
  if (IS_PERIPHERAL_REG(p_reg, POWER,, _S)) {
    return CLOCK_POWER_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, CLOCK,, _S)) {
    return CLOCK_POWER_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 0, _S)) {
    return SERIAL0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 1, _S)) {
    return SERIAL1_IRQn;
  /* 10 SPIM4 */
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 2, _S)) {
    return SERIAL2_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, UARTE, 3, _S)) {
    return SERIAL3_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, GPIOTE, 0, _S)) {
    return GPIOTE0_IRQn;
  /* 14 SAADC */
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 0, _S)) {
      return TIMER0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 1, _S)) {
      return TIMER1_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, TIMER, 2, _S)) {
      return TIMER2_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RTC, 0, _S)) {
      return RTC0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, RTC, 1, _S)) {
      return RTC1_IRQn;
  /* 24, 25 WDT0,1 */
  /* 26 COMP */
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 0, _S)) {
      return EGU0_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 1, _S)) {
        return EGU1_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 2, _S)) {
        return EGU2_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 3, _S)) {
        return EGU3_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 4, _S)) {
        return EGU4_IRQn;
  } else if (IS_PERIPHERAL_REG(p_reg, EGU, 5, _S)) {
        return EGU5_IRQn;
  /* 33-36 PWM0-3*/
  /* 38 PDM0 */
  /* 40 I2S */
  } else if (IS_PERIPHERAL_REG(p_reg, IPC,, _S)) {
    return IPC_IRQn;
  /* 43 QPSI */
  /* 45 NFCT */
  } else if (IS_PERIPHERAL_REG(p_reg, GPIOTE, 1, _NS)) {
    return GPIOTE1_IRQn;
  /* 51,52 QDEC0,1*/
  /* 54 USBD*/
  /* 55 USBREGULATOR*/
  /* 57 KMU */
  /* 68 CRYPTOCELL */
  }
#endif
  else {
    NOT_KNOWN_PER_ERROR;
    return 0; /* unreachable */
  }
}
