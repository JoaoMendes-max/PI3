/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef _AMEBA_PMU_H_
#define _AMEBA_PMU_H_

typedef enum {
	PMU_OS					= 0,
	PMU_WLAN_DEVICE		= 1,
	PMU_LOGUART_DEVICE	= 2,
	PMU_KM4_RUN			= 3,

	PMU_UART0_DEVICE		= 4,
	PMU_UART1_DEVICE		= 5,
	PMU_I2C0_DEVICE		= 6,
	PMU_TOUCH_DEVICE		= 7,
	PMU_USOC_DEVICE		= 8,
	PMU_DONGLE_DEVICE	= 9,
	PMU_RTC_DEVICE		= 10,
	PMU_CONSOL_DEVICE	= 11,
	PMU_ADC_DEVICE	= 12,
	PMU_WAKWLOCK_TIMEOUT = 13,
	PMU_KEYSCAN_DEVICE	= 14,
	PMU_PSRAM_DEVICE	= 15,
	PMU_SDIO_DEVICE		= 16,
	PMU_DHCP_PROCESS,
	PMU_LWIP_STACK,
	PMU_DEV_USER_BASE, /* reserved for customer use */

	PMU_MAX				= 31
} PMU_DEVICE;

enum SLEEP_TYPE {
	SLEEP_PG	= 0,
	SLEEP_CG	= 1,
};

// default locked by OS and not to sleep until OS release wakelock in somewhere
#if defined (CONFIG_ARM_CORE_CM4)
#define DEFAULT_WAKELOCK		(BIT(PMU_OS))
#else
#define DEFAULT_WAKELOCK		(BIT(PMU_OS))
#endif
#define DEFAULT_DEEP_WAKELOCK		(BIT(PMU_OS))
#define PMU_SLEEP_FOREVER		(uint32_t) 0xffffffffUL

typedef uint32_t (*PSM_HOOK_FUN)(unsigned int, void *param_ptr);

#define PMU_DEVICE_TIMER_DEFAULT_INTERVAL	2000
#define PMU_DEVICE_TIMER_MAX_INTERVAL		(1000*30) /* max 30sec */

typedef struct {
	uint32_t					nDeviceId;
	PSM_HOOK_FUN		sleep_hook_fun;
	void				*sleep_param_ptr;
	PSM_HOOK_FUN		wakeup_hook_fun;
	void				*wakeup_param_ptr;
} PSM_DD_HOOK_INFO;

uint32_t pmu_yield_os_check(void);
uint32_t pmu_exec_sleep_hook_funs(void);
void pmu_exec_wakeup_hook_funs(uint32_t nDeviceIdMax);
uint32_t pmu_set_sleep_type(uint32_t type);
uint32_t pmu_get_sleep_type(void);
uint32_t pmu_get_sleep_time(void);
void pmu_set_max_sleep_time(uint32_t timer_ms);
void pmu_set_sleep_time_range(uint32_t min_time, uint32_t max_time);
#ifndef CONFIG_BUILD_ROM
void pmu_deepsleep_cmd(uint32_t NewStatus);
#endif
void pmu_tickless_debug(uint32_t NewStatus);

void pmu_set_dsleep_active_time(uint32_t TimeOutMs);
void pmu_acquire_deepwakelock(uint32_t nDeviceId);
void pmu_release_deepwakelock(uint32_t nDeviceId);

void pmu_set_dev_wakeup_tick(uint32_t nDeviceId, uint32_t Ms);
uint32_t pmu_set_sysactive_time(uint32_t timeout);
void pmu_register_sleep_callback(uint32_t nDeviceId, PSM_HOOK_FUN sleep_hook_fun, void *sleep_param_ptr, PSM_HOOK_FUN wakeup_hook_fun, void *wakeup_param_ptr);
void pmu_unregister_sleep_callback(uint32_t nDeviceId);

int freertos_ready_to_sleep(void);
int freertos_ready_to_dsleep(void);
void freertos_pre_sleep_processing(unsigned int *expected_idle_time);
void freertos_post_sleep_processing(unsigned int *expected_idle_time);

void pmu_acquire_wakelock(uint32_t nDeviceId);
void pmu_release_wakelock(uint32_t nDeviceId);
uint32_t pmu_get_wakelock_status(void);
uint32_t pmu_get_deepwakelock_status(void);
/**
  * @brief  set roaming awake or not
  * @param  enable/threshhold:
  			1: enable roaming awake and set the threshhold
  			0: disable roaming awake and ignore the threshhold
  * @retval none
  */
void pmu_set_roaming_awake(uint8_t enable, uint8_t threshhold, uint8_t winsize);
void pmu_reset_awake(uint8_t type);
void pmu_degrade_awake(uint8_t type);

extern uint32_t tickless_debug;
extern uint32_t tick_last_tcp;
extern uint32_t system_can_yield;

#endif
