#ifndef __RTL8852AU_LOGGING_H
#define __RTL8852AU_LOGGING_H

#include <linux/kernel.h> // Für pr_info, pr_warn, pr_err usw.

// Präfix für alle Log-Ausgaben
#define RTL8852AU_PREFIX "rtl8852au: "

// Makros für einheitliche Ausgaben
#define RTL8852AU_INFO(fmt, ...) \
    pr_info(RTL8852AU_PREFIX fmt, ##__VA_ARGS__)

#define RTL8852AU_WARN(fmt, ...) \
    pr_warn(RTL8852AU_PREFIX fmt, ##__VA_ARGS__)

#define RTL8852AU_ERR(fmt, ...) \
    pr_err(RTL8852AU_PREFIX fmt, ##__VA_ARGS__)

#endif // __RTL8852AU_LOGGING_H
