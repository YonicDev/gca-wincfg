#!/usr/bin/env node

const yargs = require('yargs')
    .usage('Usage: gca-config --path [path]')
    .help('h')
    .alias('h','help')
    .describe('p','Path to store the drivers to be installed')
    .alias('p','path');

const argv = yargs.argv;

var path,errorCode;

if(argv.h) {
    yargs.showHelp();
    process.exit(0);
}

if(argv.p==""||argv.p===true) {
    console.error("[GCA-WINCFG|PARSE ERROR] You must specify a valid path.");
    process.exit(100);
} else if(argv.p!=null){
    path = argv.p!=null? argv.p : "C:\\gca\\drivers";
} else {
    path = "C:\\gca\\drivers";
}

console.log("[GCA-WINCFG|LOG] Using path " + path);

const gca = require('gca-wincfg')

if (gca.GetAdapter().driver == "WinUSB") {
    console.log("[GCA-WINCFG|LOG] This Gamecube Adapter already has the correct driver installed. Won't do anything.");
    errorCode = 0;
} else {
    console.log("[GCA-WINCFG|LOG] This Gamecube Adapter doesn't have the correct driver installed. This program will automatically configure it.");
    errorCode = gca.PrepareAdapterDriver(path, "WUP-028.inf");
    if (errorCode === 0) {
        console.log("[GCA-WINCFG|LOG] Your system is ready to install the new driver.");
        errorCode = gca.InstallAdapterDriver(path, "WUP-028.inf");
        if (errorCode === 0) {
            console.log("[GCA-WINCFG|LOG] Successfully installed the driver to the GameCube Adapter.");
        } else {
            console.error("[GCA-WINCFG|ERROR] Could not install the driver. (ERROR CODE: " +errorCode+")");
        }
    } else
        console.error("[GCA-WINCFG|ERROR] It wasn't possible to prepare your system to install the new driver. (ERROR CODE: " + errorCode+")");
};

process.exit(errorCode);
