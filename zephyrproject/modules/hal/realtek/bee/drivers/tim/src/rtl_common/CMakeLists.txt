# Copyright (c) 2026, Realtek Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_REALTEK_BEE_TIM rtl_tim.c)
zephyr_library_sources_ifdef(CONFIG_REALTEK_BEE_ENHTIM rtl_enh_tim.c)
