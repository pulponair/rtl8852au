#include <net/mac80211.h>
#include <rtl8852au.h>

#include <linux/ieee80211.h>
#include <linux/kernel.h>
#include <linux/printk.h>
#include <mac80211.h>

static int rtl8852au_start(struct ieee80211_hw *hw) {
    pr_info("rtl8852au: start called\n");
    return 0;
}

static void rtl8852au_stop(struct ieee80211_hw *hw) {
    pr_info("rtl8852au: stop called\n");
}


static int rtl8852au_config(struct ieee80211_hw *hw, u32 changed) {
    pr_info("rtl8852au: config called\n");
    return 0;
}

static int rtl8852au_add_interface(struct ieee80211_hw *hw,
                                   struct ieee80211_vif *vif) {
    pr_info("rtl8852au: add_interface called\n");
    return 0;
}

static void rtl8852au_remove_interface(struct ieee80211_hw *hw,
                                       struct ieee80211_vif *vif) {
    pr_info("rtl8852au: remove_interface called\n");
}

static void rtl8852au_configure_filter(struct ieee80211_hw *hw,
                                       unsigned int changed_flags,
                                       unsigned int *total_flags,
                                       u64 multicast) {
    pr_info("rtl8852au: configure_filter called\n");
}

static void rtl8852au_wake_tx_queue(struct ieee80211_hw *hw,
                                    struct ieee80211_txq *txq) {
    pr_info("rtl8852au: wake_tx_queue called\n");
}


static void rtl8852au_tx(struct ieee80211_hw *hw,
                         struct ieee80211_tx_control *control,
                         struct sk_buff *skb) {

    pr_info("rtl8852au: tx called\n");
    dev_kfree_skb(skb); 
}


static int rtl8852au_sta_state(struct ieee80211_hw *hw,
                               struct ieee80211_vif *vif,
                               struct ieee80211_sta *sta,
                               enum ieee80211_sta_state old_state,
                               enum ieee80211_sta_state new_state) {

    pr_info("rtl8852au: sta_state called: %d -> %d\n", old_state, new_state);
    return 0;
}


static const struct ieee80211_ops rtl8852au_ops = {
    .start = rtl8852au_start,
    .stop = rtl8852au_stop,
    .config = rtl8852au_config,
    .add_interface = rtl8852au_add_interface,
    .remove_interface = rtl8852au_remove_interface,
    .configure_filter = rtl8852au_configure_filter,
    .wake_tx_queue = rtl8852au_wake_tx_queue,
    .tx = rtl8852au_tx,
    .sta_state = rtl8852au_sta_state, /* Optional */
};

struct ieee80211_hw *rtl8852au_mac80211_alloc(struct rtl8852au_usb *usb) {
    struct ieee80211_hw *hw;
    struct rtl8852au_priv *priv;

    hw = ieee80211_alloc_hw(sizeof(struct rtl8852au_priv), &rtl8852au_ops);
    if (!hw) {
        pr_err("Failed to allocate ieee80211_hw\n");
        return NULL;
    }

    pr_info("ieee80211_hw allocated");

    priv = hw->priv;
    priv->hw = hw;
    priv->usb = usb;

    return hw;
}

void rtl8852au_mac80211_free(struct ieee80211_hw *hw) {
    ieee80211_unregister_hw(hw);
    ieee80211_free_hw(hw);
}
