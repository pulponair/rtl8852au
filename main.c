#include <linux/module.h>
#include "usb.h"
#include "logging.h"

static int __init rtl8852au_init(void)
{
    int ret;

    RTL8852AU_INFO("Initializing driver\n");

    /* Init  USB */
    ret = rtl8852au_usb_init();
    if (ret) {
        RTL8852AU_ERR("Failed to initialize USB\n");
        return ret;
    }

    return 0;
}

static void __exit rtl8852au_exit(void)
{
    rtl8852au_usb_exit();
    RTL8852AU_INFO("driver unloaded\n");
}

module_init(rtl8852au_init);
module_exit(rtl8852au_exit);


MODULE_LICENSE("GPL");
MODULE_AUTHOR("Nikolas Hagelstein");
MODULE_DESCRIPTION("RTL8852AU mac80211-based driver");