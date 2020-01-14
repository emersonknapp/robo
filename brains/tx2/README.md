# TX2 Robo Brains

## First time setup

The "quick start guide" that comes with it should be called the "super slow bulky setup guide"

* Connect the microUSB serial cable
* Turn on the TX2
* `screen /dev/ttyACM0 115200`
* Just follow the setup instructions, works fine (wifi connection may fail the first time, try again)
* When done, reboot the tx2
* When it's back up you can SSH in via IPv6
  * `ssh USER@fe80::1%INTERFACE` (interface e.g. `enp0s20f0u3`, check ifconfig)

Install generic tools
```
sudo apt update
sudo apt install dkms
```

Install xpad driver (instructions from https://github.com/paroj/xpad)
```
sudo git clone https://github.com/paroj/xpad.git /usr/src/xpad-0.4
sudo dkms install -m xpad -v 0.4
```

## Notes for later
### Custom Kernel Build
https://docs.nvidia.com/jetson/l4t/index.html#page/Tegra%2520Linux%2520Driver%2520Package%2520Development%2520Guide%2Fkernel_custom.html%23wwpID0E0SD0HA

Release tag: tegra-l4t-r32.3.1

Grabbed `source_sync.sh` script from the sdkmanage downloads dir

* Follow the building directions in the documentation AFTER changing tegra_defconfig to include the xpad options
* Copy arm/arch/boot/Image to /boot/Image
* Copy arm/arch/boot/dts/* to /boot/dtb/
* Restart the device and we're golden

### Scraping out the tools

You can use a VirtualBox to run the SDKManager, if on Ubuntu 19 (e.g. popos laptop)

Do the whole build then skip the flash, now `~/nvidia/nvidia_sdk/JetPack_4.3_Linux_P3310/Linux_for_Tegra` has a lot of assets, including the root file system.

Where is `tegraflash.py`?

### Flashing from VM
Couldn't get it to work, just use an Ubuntu 18 box for running the SDKManager
