/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include "nrfx.h"
#if defined(NRF5340_XXAA_NETWORK)
#include "hal/nrf_aar.h"
#include "hal/nrf_ccm.h"
#include "hal/nrf_ecb.h"
#include "hal/nrf_ipc.h"
#include "hal/nrf_radio.h"
#include "hal/nrf_rng.h"
#include "hal/nrf_temp.h"

#include "hal/nrf_clock.h"
#include "hal/nrf_dppi.h"
#include "hal/nrf_egu.h"
#include "hal/nrf_gpiote.h"
#include "hal/nrf_ipc.h"
#include "hal/nrf_rtc.h"
#include "hal/nrf_timer.h"
#include "hal/nrf_uarte.h"
#elif defined(NRF5340_XXAA_APPLICATION)
#include "hal/nrf_clock.h"
#include "hal/nrf_dppi.h"
#include "hal/nrf_egu.h"
#include "hal/nrf_gpiote.h"
#include "hal/nrf_ipc.h"
#include "hal/nrf_rtc.h"
#include "hal/nrf_timer.h"
#include "hal/nrf_uarte.h"
#endif

#include "nrf_hack_int.h"

void nrf_hack_get_task_from_ptr(void *task_reg,
                                       void **p_reg,
                                       subscribe_set_f *set_f,
                                       subscribe_clear_f *clear_f,
                                       task_trigger_f *trigger_f,
                                       int *task)
{
#if defined(NRF5340_XXAA_NETWORK)
  /*IF_PER(POWER, , _NS, power)
  } else*/ IF_PER(CLOCK, , _NS, clock)
  } else IF_PER(RADIO, , _NS, radio)
  } else IF_PER(RNG, , _NS, rng)
  } else IF_PER(GPIOTE, , _NS, gpiote)
  /* 11 WDT */
  } else IF_PER(TIMER, 0, _NS, timer)
  } else IF_PER(ECB, , _NS, ecb)
  } else IF_PER(AAR, , _NS, aar)
  } else IF_PER(CCM, , _NS, ccm)
  } else IF_PER(DPPIC, , _NS, dppi)
  } else IF_PER(TEMP, , _NS, temp)
  } else IF_PER(RTC, 0, _NS, rtc)
  } else IF_PER(IPC, , _NS, ipc)
  } else IF_PER(UARTE, 0, _NS, uarte)
  } else IF_PER(EGU, 0, _NS, egu)
  } else IF_PER(RTC, 1, _NS, rtc)
  } else IF_PER(TIMER, 1, _NS, timer)
  } else IF_PER(TIMER, 2, _NS, timer)
#elif defined(NRF5340_XXAA_APPLICATION)
  /*IF_PER(DCNF, , _NS, dcnf)
  } else IF_PER(FPU, , _NS, fpu)
  } else IF_PER(CACHE, , _NS, cache)
  } else IF_PER(SPU, , _NS, spu)
  } else IF_PER(OSCILLARTORS, , _NS, oscillators)
  } else IF_PER(REGULATORS, , _NS, regulators)
  } else */ IF_PER(CLOCK, , _NS, clock)
  /*} else IF_PER(POWER, , _NS, power)
  } else IF_PER(RESET, , _NS, reset)
  } else IF_PER(CTRLAP, , _NS, ctrlap)
  } else IF_PER(SPIM, 0, _NS, spi) */
  } else IF_PER(UARTE, 0, _NS, uarte)
  /*} else IF_PER(SPIM, 1, _NS, spi)*/
  } else IF_PER(UARTE, 1, _NS, uarte)
  /*} else IF_PER(SPIM, 4, _NS, spi)
  } else IF_PER(SPIM, 2, _NS, spi)*/
  } else IF_PER(UARTE, 2, _NS, uarte)
  /*} else IF_PER(SPIM, 3, _NS, spi) */
  } else IF_PER(UARTE, 3, _NS, uarte)
  } else IF_PER(GPIOTE, 0, _S, gpiote)
  /*} else IF_PER(SAADC, , _NS, saadc)*/
  } else IF_PER(TIMER, 0, _NS, timer)
  } else IF_PER(TIMER, 1, _NS, timer)
  } else IF_PER(TIMER, 2, _NS, timer)
  } else IF_PER(RTC, 0, _NS, rtc)
  } else IF_PER(RTC, 1, _NS, rtc)
  } else IF_PER(DPPIC, , _NS, dppi)
  /*} else IF_PER(WDT0, , _NS, dppi)
  } else IF_PER(WDT1, , _NS, dppi)
  } else IF_PER(COMP, , _NS, dppi)*/
  } else IF_PER(EGU, 0, _NS, egu)
  } else IF_PER(EGU, 1, _NS, egu)
  } else IF_PER(EGU, 2, _NS, egu)
  } else IF_PER(EGU, 3, _NS, egu)
  } else IF_PER(EGU, 4, _NS, egu)
  } else IF_PER(EGU, 5, _NS, egu)
  /*} else IF_PER(PWM0, , _NS, dppi)
  } else IF_PER(PWM1, , _NS, dppi)
  } else IF_PER(PWM2, , _NS, dppi)
  } else IF_PER(PWM3, , _NS, dppi)
  } else IF_PER(PDM0, , _NS, dppi)
  } else IF_PER(I2S0, , _NS, dppi)*/
  } else IF_PER(IPC, , _NS, ipc)
  /* QSPI, NFCT */
#endif
  } else {
    NOT_KNOWN_TASK_ERROR;
    return; /* unreachable */
  }
}
