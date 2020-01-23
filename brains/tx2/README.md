# Tx2 brain for kobuki homey

## Flash the board
Download the SDK manager and install the latest L4T without the extra components.

## Upgrade XUSB
XUSB USB3 firmware is broken, it needs an update

```
1.Copy the firmware xusb_sil_rel_fw_1206 to TX2
2.Replace the firmware in initrd image
  $ sudo apt-get update
  $ sudo apt-get install cpio
  $ mkdir initrd_work
  $ cd initrd_work
  $ sudo cp /boot/initrd ./
  $ sudo gunzip -dc ./initrd  |  sudo cpio -idm
  $ sudo rm ./initrd
  $ sudo cp <LOCATE OF THE FIRMWARE> ./lib/firmware/tegra18x_xusb_firmware
  $ sudo find . | sudo cpio --quiet -H newc -o | sudo gzip -9 -n > ./initrd
  $ sudo cp initrd /boot/initrd
3.Reboot the device
  $ sudo reboot
```

## Build custom kernel

Reasons for doing:
* Enable xpad LEDs

We are following the instructions here:
https://docs.nvidia.com/jetson/l4t/index.html#page/Tegra%2520Linux%2520Driver%2520Package%2520Development%2520Guide%2Fkernel_custom.html%23

Download using tag: tegra-l4t-r32.3.1

```
./source_sync.sh -t tegra-l4t-r32.3.1

export TEGRA_KERNEL_OUT=~/dev/homey/brains/tx2/customkernel
mkdir -p $TEGRA_KERNEL_OUT
export CROSS_COMPILE=~/dev/tools/gcc-linaro-7.3.1-2018.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
export LOCALVERSION=-tegra
cd sources/kernel/kernel-4.9
make ARCH=arm64 O=$TEGRA_KERNEL_OUT tegra_defconfig
```

Modify the config

```
# $TEGRA_KERNEL_OUT/sources/.config
CONFIG_JOYSTICK_XPAD_LEDS=y
```

Build

```
make ARCH=arm64 O=$TEGRA_KERNEL_OUT -j12
```

Copy over the artifacts

```
scp $TEGRA_KERNEL_OUT/arch/arm64/boot/Image "user@[fe80::1%enp0s20u2]":~
scp -r $TEGRA_KERNEL_OUT/arch/arm64/boot/dts "user@[fe80::1%enp0s20u2]":~

# on the board
sudo cp Image /boot/Image
sudo cp dts/* /boot/dtb/
sudo reboot now
```

## Networking

```
## On host
scp netplan-config.yml tx2

## On tx2
sudo apt install netplan.io
sudo cp netplan-config.yml /etc/netplan/config.yaml
sudo netplan apply
```
