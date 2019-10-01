# Robobrains

## Prereqs
Using BalenaOS for easy setup

Install cli https://github.com/balena-io/balena-cli/blob/master/INSTALL.md

Download dev rpi3 image https://files.resin.io/resinos/raspberrypi3/2.43.0%2Brev1.dev/image/balena.img.zip


## Configuring image
Run `balena local configure balena.img`

Mount and copy `resin-eth` to `/system-connections` on the image

## Connecting
Give yourself a static eth ip `192.168.1.1` and make sure routing works.

```
ssh root@192.168.1.111 -p 22222
```

## Local cross-arch container workflows

Enable experimental features

```
# /etc/docker/daemon.json
"experimental": true,
```

To pull an off-arch container, use `--platform`

```
docker pull --platform arm64 ros:dashing-ros-core-bionic
```

To run locally, mount the correct qemu

```
docker run -it --rm -v /usr/bin/qemu-aarch64-static:/usr/bin/aarch64-static ros:dashing-ros-core-bionic
```

NOTE: you don't seem to be able to store multiple archs at the same time so have to re-pull.
