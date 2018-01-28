var gca = require('gca-wincfg');
var errorCode;

if (gca.GetAdapterDriver() == "WinUSB") {
    console.log("[GCA-WINCFG|LOG] This Gamecube Adapter already has the correct driver installed. Won't do anything.");
} else {
    console.log("[GCA-WINCFG|LOG] This Gamecube Adapter doesn't have the correct driver installed. This program will automatically configure it.");
    errorCode = gca.PrepareAdapterDriver("C:\\gca\\drivers", "WUP-028.inf");
    if (errorCode === 0) {
        console.log("[GCA-WINCFG|LOG] Your system is ready to install the new driver.");
        errorCode = gca.InstallAdapterDriver("C:\\gca\\drivers", "WUP-028.inf");
        if (errorCode === 0) {
            console.log("[GCA-WINCFG|LOG] Successfully installed the driver to the GameCube Adapter.");
        } else {
            console.log("[GCA-WINCFG|ERROR] Could not install the driver. (ERROR CODE: " +errorCode+")");
        }
    } else
        console.error("[GCA-WINCFG|ERROR] It wasn't possible to prepare your system to install the new driver. (ERROR CODE: " + errorCode+")");
};
