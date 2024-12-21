#include <linux/usb.h>
#include <usb.h>
#include <rtl8852au.h>
#include <mac80211.h>

static const struct usb_device_id rtl8852au_table[] = {    
    { USB_DEVICE(0x2357, 0x013f) }, //TP-Link 802.11ac WLAN Adapter
    {}
};

MODULE_DEVICE_TABLE(usb, rtl8852au_table);

static int rtl8852au_probe(struct usb_interface *interface, const struct usb_device_id *id)
{
    struct ieee80211_hw *hw;
	struct rtl8852au_usb *usb;
    struct usb_device *device = interface_to_usbdev(interface);

    pr_info("rtl8852au USB device connected\n");

    usb = kzalloc(sizeof(*usb), GFP_KERNEL);
    if (!usb) {
        dev_err(&interface->dev, "Failed to allocate rtl8852au_usb\n");
        return -ENOMEM;
    }

    usb->device = usb_get_dev(device);
    usb->interface = interface;

    hw = rtl8852au_mac80211_alloc(usb);



    return 0;
}

static void rtl8852au_disconnect(struct usb_interface *intf)
{
    pr_info("rtl8852au USB device disconnected\n");
}

static struct usb_driver rtl8852au_usb_driver = {
    .name = "rtl8852au",
    .id_table = rtl8852au_table,
    .probe = rtl8852au_probe,
    .disconnect = rtl8852au_disconnect,
};

int rtl8852au_usb_init(void)
{
    return usb_register(&rtl8852au_usb_driver);
}

void rtl8852au_usb_exit(void)
{
    usb_deregister(&rtl8852au_usb_driver);
}