# gca-wincfg

[![Build status](https://ci.appveyor.com/api/projects/status/py0lk9bq06axg2m8/branch/master?svg=true)](https://ci.appveyor.com/project/yonicstudios/gca-wincfg/branch/master)

This is the Configuration Module which allows the Nintendo&reg; Wii U&trade; GameCube Adapter to be used in Windows. Although it is designed to be used in Node.js applications such as [gca-js](https://github.com/YonicDev/gca-js) and [gca-node](https://github.com/YonicDev/gca-node), the source code can be extended to C++ applications, such as [gca+](https://github.com/YonicDev/gca-plus).

## Requirements
* Windows 7 or newer (64-bit only, there is no planned support for 32-bit).
* Node.js 7.x
* A Nintendo&reg; Wii U&trade; GameCube Adapter

## Usage
gca-wincfg is intended for developers to automatize the configuration of the Nintendo&reg; Wii U&trade; GameCube Adapter in their games. For consumer purposes, manually configure it with [Zadig](http://zadig.akeo.ie/).

To add gca-wincfg to your project, install it as an npm package.
```
npm install gca-wincfg
```
> **NOTE:** In versions prior to 1.1.0, move the libwbdi.dll from this repository to your node package root folder.

From 1.2.0, you can use gca-wincfg in two different ways, or "flavors".

> ***NOTE:*** Since gca-wincfg requires administrator privileges, you must run gca-wincfg as an elevated subprocess. This can be done with [elevator](https://github.com/resin-io-modules/elevator) on Windows-only applications or [sudo-prompt](https://github.com/jorangreef/sudo-prompt) for cross-platform applications.

### Script flavor

You can write a script to customize the configuration done by gca-wincfg, which is useful for graphical applications.

To use gca-wincfg in your code, add the following to the scripts where you want to use it:

```
var gca_config = require('gca-wincfg');
```

The simplest structure of configuration is shown in [examples/config.js](https://github.com/YonicDev/gca-wincfg/blob/master/examples/config.js), alongside a couple of logs. There can be anything in-between the functions in this basic skeleton, but these three functions must be called in that order.

More information about the functions of gca-wincfg can be found at the wiki.

As for error handling, gca-wincfg returns the same error codes as [libwdi](https://github.com/pbatard/libwdi).

### Command flavor

From 1.2.0, you can also use a binary CLI utility tool included with gca-wincfg named `gca-config`, which uses a basic configuration script. This flavor is useful for npm `postinstall` subroutines, or command-line tools/applications.

Use the following syntax in a command window to run the tool:

```
X:\project\root\folder> .\node_modules\.bin\gca-config --path [path]
```

`path` is the location at which the driver files are saved in order to install them into the adapter. It defaults to `C:\gca\drivers`.

##  FAQ

### Does gca-wincfg support 32-bit platforms?
No, and we don't plan to add support for 32-bit platforms anytime soon, as [less than 3% of Steam users are using a Windows 32-bit operating system](https://www.statista.com/statistics/265033/proportion-of-operating-systems-used-on-the-online-gaming-platform-steam/).

### What about other operating systems?
Mac OS and Linux have different configurations from Windows, which can be done automatically.
* In Mac OS, an [installer](https://forums.dolphin-emu.org/attachment.php?aid=13495) does this automatically.
* In Linux, the configuration is done manually for the moment, although gca-node and gca-js will eventually configure this automatically.

BSD and other OS are not officially supported.
