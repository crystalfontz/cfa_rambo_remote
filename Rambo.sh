#!/bin/sh

cd /home/root/Test

/etc/init.d/xserver-nodm stop

export TSLIB_TSDEVICE=/dev/input/touchscreen0
export QWS_MOUSE_PROTO=tslib:/dev/input/touchscreen0

if [ ! -e /etc/pointercal ]; then
	ts_calibrate
fi

./RamboRemote -qws

/etc/init.d/xserver-nodm start



