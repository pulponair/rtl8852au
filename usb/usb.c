#include <linux/usb.h>
#include "usb.h"
#include "rtl8852au.h"
#include "mac80211.h"
#include "logging.h"
#include <net/mac80211.h>

static int rtl8852au_probe(struct usb_interface *interface,
                          const struct usb_device_id *id)
{
    struct ieee80211_hw *hw;
    struct rtl8852au_usb *usb;
    struct usb_device *device = interface_to_usbdev(interface);
    int ret;

    RTL8852AU_INFO("USB device connected\n");

    usb = kzalloc(sizeof(*usb), GFP_KERNEL);
    if (!usb) {
        dev_err(&interface->dev, "Failed to allocate rtl8852au_usb\n");
        return -ENOMEM;
    }

    usb->device = usb_get_dev(device);
    usb->interface = interface;
    usb_set_intfdata(interface, usb);

    hw = rtl8852au_mac80211_alloc(usb);
    if (!hw) {
        dev_err(&interface->dev, "Failed to allocate ieee80211_hw\n");
        ret = -ENOMEM;
        goto err_free_usb;
    }

    ret = rtl8852au_mac80211_register(hw);
    if (ret)
        goto err_free_hw;

    return 0;

err_free_hw:
    rtl8852au_mac80211_free(hw);
err_free_usb:
    usb_put_dev(usb->device);
    kfree(usb);
    return ret;
}

static void rtl8852au_disconnect(struct usb_interface *interface)
{
    struct rtl8852au_usb *usb = usb_get_intfdata(interface);
    struct rtl8852au_priv *priv;
    struct ieee80211_hw *hw;

    if (!usb)
        return;

    hw = usb_get_intfdata(interface);
    if (!hw)
        goto free_usb;

    priv = hw->priv;
    if (!priv)
        goto free_hw;

    rtl8852au_mac80211_unregister(hw);
    rtl8852au_mac80211_free(hw);

free_hw:
    rtl8852au_mac80211_free(hw);
free_usb:
    usb_put_dev(usb->device);
    kfree(usb);
}

static const struct usb_device_id rtl8852au_id_table[] = {
    { USB_DEVICE(0x0bda, 0x8852) }, // Replace with actual VID/PID
    { }
};
MODULE_DEVICE_TABLE(usb, rtl8852au_id_table);

static struct usb_driver rtl8852au_driver = {
    .name = "rtl8852au",
    .id_table = rtl8852au_id_table,
    .probe = rtl8852au_probe,
    .disconnect = rtl8852au_disconnect,
};

int rtl8852au_usb_init(void)
{
    return usb_register(&rtl8852au_driver);
}
EXPORT_SYMBOL_GPL(rtl8852au_usb_init);

void rtl8852au_usb_exit(void)
{
    usb_deregister(&rtl8852au_driver);
}
EXPORT_SYMBOL_GPL(rtl8852au_usb_exit);
