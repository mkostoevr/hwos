#pragma once

#include <stdarg.h>
#include <kernel/types.h>
#include <kernel/lib/string.h>
#include "termcolors.h"

#define FDO_KERNEL "[KERNEL]: "
#define FDO_ARCH_i686 "[ARCH i686]: "
#define FDO_PHYSMEM "[PMM]: "

#ifdef __cplusplus
extern "C" {
#endif

void printk_dup(const char *fmt, ... );
void printk_screen(const char *fmt, ... );
void printk_log(const char *fmt, ... );

void fdo_set_putchar_log_callback(void (*p)(char));
void fdo_set_putchar_screen_callback(void (*p)(char));

#ifdef __cplusplus
}
#endif

