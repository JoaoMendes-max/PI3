/*
 * Copyright (c) 2026, Realtek Semiconductor Corporation
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*============================================================================*
 *                      Define to prevent recursive inclusion
 *============================================================================*/
#ifndef SYSTEM_INIT_NS_H
#define SYSTEM_INIT_NS_H

/*============================================================================*
 *                      Headers
 *============================================================================*/
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

/*============================================================================*
 *                      Variables
 *============================================================================*/

extern uint32_t SystemCoreClock;
extern void (*hal_setup_hardware)(void);
extern void (*hal_setup_cpu)(void);
extern void (*hal_setup_fpu)(void);
extern bool (*mpu_setup)(void);
extern void (*system_restore)(void);
extern void (*dvfs_init)(void);
extern void (*phy_hw_control_init)(bool);
extern void (*phy_init)(uint8_t);
extern void (*thermal_tracking_timer_init)(void);
extern void (*ft_paras_apply)(void);
extern void (*si_flow_data_init)(void);
extern void (*secure_os_func_ptr_init)(void);
extern void secure_os_func_ptr_init_rom(void);
extern void (*secure_platform_func_ptr_init)(void);
extern bool (*log_buffer_init)(void);
extern void (*log_gdma_init)(void);
extern void (*platform_rtc_aon_init)(void);
extern void (*power_manager_master_init)(void);
extern void (*power_manager_slave_init)(void);
extern void (*platform_pm_init)(void);
extern void (*pmu_power_on_sequence_restart)(void);
extern void (*pmu_apply_voltage_tune)(void);
extern void hw_aes_mutex_init(void);
extern void os_queue_func_init(void);
extern bool (*os_register_pm_excluded_handle)(void **pp_handle, int type);
extern bool (*os_unregister_pm_excluded_handle)(void **pp_handle, int type);
extern bool os_register_pm_excluded_handle_imp(void **handle, int type);
extern bool os_unregister_pm_excluded_handle_imp(void **handle, int type);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_INIT_NS_H */
