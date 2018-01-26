# gca-wincfg
[![Build status](https://ci.appveyor.com/api/projects/status/py0lk9bq06axg2m8?svg=true)](https://ci.appveyor.com/project/yonicstudios/gca-wincfg)


This is the Configuration Module which allows the Nintendo&reg; Wii U&trade; GameCube Adapter to be used in Windows. Although it is designed to be used in Node.js applications such as [gca-js](https://github.com/YonicDev/gca-js) and [gca-node](https://github.com/YonicDev/gca-node), the source code can be extended to C++ applications, such as gca+. 

## Requirements
* Windows 7 or newer (64-bit only, there is no planned support for 32-bit).
* Node.js 7.x
* A Nintendo&reg; Wii U&trade; GameCube Adapter

## Usage
gca-wincfg is intended for developers to automatize the configuration of the Nintendo&reg; Wii U&trade; GameCube Adapter in their games. For consumer purposes, manually configure it with [Zadig](http://zadig.akeo.ie/).
The simplest structure of configuration is shown in [examples/config.js](https://github.com/YonicDev/gca-wincfg/blob/master/examples/config.js).
As for error handling, gca-wincfg returns the same error codes as [libwdi](https://github.com/pbatard/libwdi).

##  FAQ

### Does gca-wincfg support 32-bit platforms?
No, and we don't plan to add support for 32-bit platforms anytime soon, as [less than 3% of Steam users are using a Windows 32-bit operating system](https://www.statista.com/statistics/265033/proportion-of-operating-systems-used-on-the-online-gaming-platform-steam/).

### What about other operating systems?
Mac OS and Linux have different configurations from Windows, which can be done automatically.
* In Mac OS, an [installer](https://forums.dolphin-emu.org/attachment.php?aid=13495) does this automatically.
* In Linux, the configuration is done manually for the moment, although gca-node and gca-js will eventually configure this automatically.

BSD and other OS are not officially supported.
