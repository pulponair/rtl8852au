#ifndef __RTL8852AU_MAC80211_H
#define __RTL8852AU_MAC80211_H

#include <linux/ieee80211.h>
#include <rtl8852au.h>

struct ieee80211_hw *rtl8852au_mac80211_alloc(struct rtl8852au_usb *usb);
int rtl8852au_mac80211_register(struct ieee80211_hw *hw);
void rtl8852au_mac80211_unregister(struct ieee80211_hw *hw);
void rtl8852au_mac80211_free(struct ieee80211_hw *hw);

#endif 