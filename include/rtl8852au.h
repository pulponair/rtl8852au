#ifndef __RTL8852AU_H
#define __RTL8852AU_H


struct rtl8852au_usb {
    struct usb_device *device;
    struct usb_interface *interface; 
};


struct rtl8852au_priv {
    struct ieee80211_hw *hw;
    struct rtl8852au_usb *usb;    
};
#endif 