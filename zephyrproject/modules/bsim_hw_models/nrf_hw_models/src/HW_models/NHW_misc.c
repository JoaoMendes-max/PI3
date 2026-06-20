/*
 * Copyright (c) 2023 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <stddef.h>
#include <stdint.h>
#include "bs_tracing.h"
#include "NHW_virt_RAM.h"
#include "nsi_tasks.h"
#include "NHW_misc_int.h"

/*
 * Get the name of a core/domain
 *
 * Only for debugging/logging/tracing purposes.
 */
const char *nhw_get_core_name(unsigned int core_n)
{
  static const char *corenames[NHW_INTCTRL_TOTAL_INST] = NHW_CORE_NAMES;

  if (core_n < sizeof(corenames)/sizeof(corenames[0])) {
    return corenames[core_n];
  } else {
    return NULL;
  }
}

/*
 * Convert an address to the real embedded device RAM into an addresses
 * in the models buffer which is used in place of the RAM.
 * Note the input is a pointer to the pointer/address, which will be modified in the call.
 *
 * This function will only modify the address if it was inside an embedded RAM known to it.
 * In that case it returns true.
 * Otherwise the address is unmodified and false is returned.
 */
bool nhw_convert_RAM_addr(void **addr)
{
#if defined(NRF5340) || defined(NRF5340_XXAA_NETWORK) || defined(NRF5340_XXAA_APPLICATION)
  if (((intptr_t)*addr >= NHW_APPCORE_RAM_ADDR) && ((intptr_t)*addr < (intptr_t)*addr + NHW_APPCORE_RAM_SIZE)) {
     *addr = (intptr_t)*addr - NHW_APPCORE_RAM_ADDR + NHW_appcore_RAM;
     return true;
  }
#else
  (void) addr;
  bs_trace_warning_time_line("%s not supported yet in this device\n", __func__);
#endif
  return false;
}

static struct simu_real_conv_table_t *simu_real_conv_table;
static uint simu_real_conv_table_size;

static void init_simu_real_conv_table(void) {
  simu_real_conv_table_size = nhw_get_simu_real_conv_table(&simu_real_conv_table);
}

NSI_TASK(init_simu_real_conv_table, HW_INIT, 999);

static void free_simu_real_conv_table(void) {
  if (simu_real_conv_table) {
    free(simu_real_conv_table);
    simu_real_conv_table = NULL;
  }
}

NSI_TASK(free_simu_real_conv_table, ON_EXIT_POST, 1);

/**
 * Convert a real peripheral base address (like 0x4000F000UL)
 * into the corresponding simulation peripheral base address
 *
 * Note: In general it is recommended to refer to peripherals
 * using the MDK macros (like NRF_TIMER0), this function
 * exists to cover the cases in which this is not possible.
 */
void *nhw_convert_periph_base_addr(void *hw_addr) {
  for (unsigned int i = 0; i < simu_real_conv_table_size; i++) {
    if (simu_real_conv_table[i].real_add == (uint32_t)hw_addr) {
      return simu_real_conv_table[i].simu_addr;
    }
  }
  bs_trace_error_time_line("Could not find real peripheral addr %p\n", hw_addr);
  return NULL;
}

/**
 * Convert a simulated peripheral address into the real
 * HW peripheral address (like 0x4000F000UL)
 *
 * Note that if there is both secure and non secure it will just return whichever was
 * earlier in simu_real_conv_table[].
 */
void *nhw_convert_per_addr_sim_to_hw(void *sim_addr) {
  for (unsigned int i = 0; i < simu_real_conv_table_size; i++) {
    intptr_t start = (intptr_t)simu_real_conv_table[i].simu_addr;
    intptr_t end = start + (intptr_t)simu_real_conv_table[i].size ;
    if (((intptr_t)sim_addr >= start) && ((intptr_t)sim_addr < end)) {
      return (void *)((intptr_t)sim_addr - start + (intptr_t)simu_real_conv_table[i].real_add);
    }
  }
  bs_trace_error_time_line("%s could not find %p in between the simulated peripherals\n", __func__, sim_addr); \
  return 0;
}

/**
 * Convert a real peripheral address (like 0x4000F000UL)
 * into the equivalent simulated HW peripheral address
 *
 * Note that if there is both secure and non secure it will always return the secure real HW address
 */
void *nhw_convert_per_addr_hw_to_sim(void *real_addr) {
  for (unsigned int i = 0; i < simu_real_conv_table_size; i++) {
    intptr_t start = (intptr_t)simu_real_conv_table[i].real_add;
    intptr_t end = start + (intptr_t)simu_real_conv_table[i].size ;
    if (((intptr_t)real_addr >= start) && ((intptr_t)real_addr < end)) {
      return (void *)((intptr_t)real_addr - start + (intptr_t)simu_real_conv_table[i].simu_addr);
    }
  }
  bs_trace_error_time_line("%s could not find %p in between the simulated peripherals\n", __func__, real_addr); \
  return 0;
}
