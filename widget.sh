#!/bin/sh
#export TZ=CST-8
export LD_LIBRARY_PATH=/lib
export QML2_IMPORT_PATH=/qml
export QML_IMPORT_PATH=/qml
export QT_QPA_FB_TSLIB=1
export QT_QPA_FONTDIR=/lib/fonts
export QT_QPA_PLATFORM=linuxfb
export QT_QPA_PLATFORM_PLUGIN_PATH=/plugins
export TSLIB_CALIBFILE=/etc/pointercal
export TSLIB_CONFFILE=/etc/ts.conf
export TSLIB_CONSOLEDEVICE=none
export TSLIB_FBDEVICE=/dev/fb0
export TSLIB_PLUGINDIR=/lib/ts
export TSLIB_TSDEVICE=/dev/input/event0

if [ ! -f "/etc/pointercal" ];then
ts_calibrate
fi

chmod 777 /app_qt5/widget
/app_qt5/widget &

