/*
 * Copyright (c) 2024 Realtek Semiconductor Corp.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

/*
 * ameba_ram_libc.h
 *
 * Definitions for RTL library functions
 */

#ifndef _AMEBA_RAM_LIBC_H_
#define	_AMEBA_RAM_LIBC_H_

#include <basic_types.h>
#include <diag.h>
#include <va_list.h>

extern int _rtl_vsprintf(char *buf, size_t size, const char *fmt, const int *dp);
extern int _rtl_printf(const char *fmt, ...);
extern int _rtl_sprintf(char *str, const char *fmt, ...);
extern int _rtl_snprintf(char *str, size_t size, const char *fmt, ...);
extern int _rtl_vsnprintf(char *buf, size_t size, const char *fmt, va_list ap);
extern int _rtl_sscanf(const char *buf, const char *fmt, ...);
#endif /* _AMEBA_RAM_LIBC_H_ */

