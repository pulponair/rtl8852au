# rtl8852au Linux Driver (Community Fork)

[![Kernel 6.x CI](https://github.com/pulponair/rtl8852au/actions/workflows/kernel-build.yml/badge.svg?branch=develop)](https://github.com/pulponair/rtl8852au/actions)

> **CI Status:** Automated builds are tested against Linux kernels **6.8**, **6.13**, **6.14**, and **6.15**.

This project is a community-maintained fork of the original Realtek USB WiFi driver
**RTL8852AU\_WiFi\_linux\_v1.15.0.1-0-g487ee886.20210714**,
which was initially maintained by Larry Finger.
After Larry's passing, this fork (maintained at [pulponair/rtl8852au](https://github.com/pulponair/rtl8852au)) continues to modernize and improve the driver for current Linux kernels.

---

## Key Improvements

* Dropped outdated kernel and platform support (**Linux 5.15+ required**, tested up to **6.15**).
* Fixed various array out-of-bounds issues and improved overall code safety.
* Improved USB initialization and streamlined module structure.
* Extended station information and debug logging.
* Removed legacy Realtek code for a cleaner, more maintainable driver.

---

## Supported Chipsets

* **rtl8832au**
* **rtl8852au**

---

## Known Supported Devices

* BUFFALO WI-U3-1200AX2(/N) – `0411:0312`
* ASUS USB-AX56 – `0b05:1997`, `0b05:1a62`
* EDUP EP-AX1696GS – `0bda:8832`
* Fenvi FU-AX1800P – `0bda:885c`
* Realtek Demo Boards – `0bda:8832`, `0bda:885a`, `0bda:885c`
* D-Link DWA-X1850 – `2001:3321`, `2001:0141`
* TP-Link AX1800 – `2357:013f`, `2357:0140`
* TP-Link Archer TX20UH – `2357:0141`
* TP-Link (vendor 0x35bc) – `35bc:0100`
* ipTIME AX2000U – `0bda:8832`
* ELECOM WDC-X1201DU3 – `056e:4020`

---

## USB Modeswitch (D-Link DWA-X1850)

Some DWA-X1850 devices appear as a USB disk (`0bda:1a2b`) with Windows drivers.
To avoid this, add the following rule to either
`/usr/lib/udev/rules.d/40-usb_modeswitch.rules` or
`/lib/udev/rules.d/40-usb_modeswitch.rules`:

```bash
# D-Link DWA-X1850 WiFi Dongle
ATTR{idVendor}=="0bda", ATTR{idProduct}=="1a2b", RUN+="usb_modeswitch '/%k'"
```

---

## Installation

### Requirements

Install `make`, `gcc`, `kernel headers`, and `git`.

**Ubuntu/Debian:**

```bash
sudo apt update
sudo apt install -y make gcc linux-headers-$(uname -r) build-essential git
```

**Fedora:**

```bash
sudo dnf install kernel-headers kernel-devel
sudo dnf group install "C Development Tools and Libraries"
```

**openSUSE:**

```bash
sudo zypper install make gcc kernel-devel kernel-default-devel git libopenssl-devel
```

**Arch Linux:**

```bash
sudo pacman -S --needed base-devel linux-headers git
```

---

### Manual Build & Install

```bash
git clone git://github.com/pulponair/rtl8852au.git
cd rtl8852au
make
sudo make install
```

After kernel updates:

```bash
cd rtl8852au
git pull
make
sudo make install
```

---

## DKMS Installation (Recommended)

**DKMS automatically rebuilds this driver when your kernel updates.**

```bash
git clone git://github.com/pulponair/rtl8852au.git
cd rtl8852au

# Add the module using its current version (auto-read from dkms.conf)
version=$(grep PACKAGE_VERSION dkms.conf | cut -d"=" -f2)
sudo dkms add .
sudo dkms build rtl8852au/${version}
sudo dkms install rtl8852au/${version}
```

To verify:

```bash
modinfo 8852au
```

**Updating via DKMS:**

```bash
cd rtl8852au
git pull
version=$(grep PACKAGE_VERSION dkms.conf | cut -d"=" -f2)
sudo dkms remove rtl8852au/${version} --all
sudo dkms add .
sudo dkms build rtl8852au/${version}
sudo dkms install rtl8852au/${version}
```

---

## Secure Boot (Optional)

If Secure Boot is enabled, sign the module:

```bash
make
sudo make
```
