# Copyright (c) 2026, Realtek Semiconductor Corporation
# SPDX-License-Identifier: Apache-2.0

if(NOT DEFINED CONFIG_REALTEK_BEE_USING_RTL876X_DRIVER)
    zephyr_include_directories(inc)
endif()

add_subdirectory(src)
