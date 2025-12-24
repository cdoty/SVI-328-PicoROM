# SVI-328 PicoROM

## Overview

SVI-328 PicoROM is a ROM emulator for Spectravideo 328 which uses a [Raspberry Pico 2 W](https://www.raspberrypi.com/products/raspberry-pi-pico-2/) microcontroller board to emulate a SVI-328 game ROM cartridge.

The Raspberry Pi Pico code has been modified to remove all of the wifi functionality and allow a 32k rom image to be compiled into the firmware.

I was unable to get the original cartridge to work with wifi, so I reduced the functionality to repurpose the cartridge. This works nicely as a development test cartridge.

![SVI-328 PicoROM cartridge](images/cartridge.jpeg "SVI-328 PicoROM cartridge")

## Repository contents

This repository contains:

 - C firmware source code ([pico](pico/) directory) for Raspberry Pi Pico 2 W responsible for dynamic ROM emulation.
 - PCB design files ([pcb](pcb/) directory), including schematics and layouts, developed using KiCad, suitable for fabrication with, for example, [PCBWay](https://www.pcbway.com/).

## Using a custom SVI ROM
Replace Test.rom in the [rom](rom/) directory, run mk.bat and recompile the firmware. You may have to touch or resave [svi-328-cartridge.c](pico/c/svi-328-cartridge.c). 

**NOTE**: Only 32 kB ROM images are supported at the moment.

The Test.rom project can be found [here](https://github.com/cdoty/SVI).

## How to get it running quickly

### Cartridge hardware

First, create the PCB by ordering it from [PCBWay](https://www.pcbway.com/) with the Gerber files provided in [release/svi-328-picorom-gerber.zip](release/svi-328-picorom-gerber.zip).

Then get a [Raspberry Pico 2 W](https://www.raspberrypi.com/products/raspberry-pi-pico-2/) (not the version 1, and make sure you order the Wi-Fi version W) and one atleast +5V diode (DigiKey part number 4878-1N4001CT-ND DIODE GEN PURP 50V 1A DO204AC works, for example).

Solder these together. :) 

### Cartridge software

Press Pico's BOOTSEL button (the only button on the board, see the board picture above) and while pressing plug it in to your computer via USB.

Then, find the UF2 flash binary file from [release/svi-328-picorom.uf2](release/svi-328-picorom.uf2).

Next, flash the Raspberry Pico 2 W by dragging the UF2 file on to the Pico USB drive and wait until Pico disconnects (displays `Disk Not Ejected Properly` in macOS) and the green LED light turns on to signal that the firmware booted correctly. Finally, remove the USB cable.

## System prerequisites

The replication and deployment of this project requires the following environment configurations:
 - Raspberry Pi Pico SDK installation and associated toolchains.
 - KiCad for PCB customization, schematic evaluation, and Gerber file generation.

The build scripts have been developed and tested with macOS Sonoma 14.6.1 and requires the following software to be installed:

 - [Visual Studio Code](https://code.visualstudio.com) 1.98.2 or newer 
 - Raspberry Pico Visual Studio Code extensions with [these](https://www.raspberrypi.com/news/get-started-with-raspberry-pi-pico-series-and-vs-code/) instructions
 - picotool 2.1.1, `brew install picotool` with [HomeBrew](https://brew.sh)
 - [z88dk version 2.3](https://github.com/z88dk/z88dk) (currently only z88dk-z80asm is used)
 - [openMSX emulator version 20.0](https://openmsx.org/) (which should be installed in /Applications/openMSX.app)
 - [Node.js version 22.12.10](https://nodejs.org/en) or newer
 - [Node Version Manager 22.12.0](https://github.com/nvm-sh/nvm) or newer (it's easier to manage Node versions with this, but you can omit this you install Node.js some other way)
 - [KiCad version 8.0.6](https://www.kicad.org/download/) or newer

## SVI-318 compatibility

The hardware will work with SVI-318 and the loader software should also work with it, altough it has not been tested on a real device yet.

## Compiling the source code

### Raspberry Pico 2 W firmware source code

The Pico firmware source code is located in [pico](pico/) directory and you can compile it by opening the folder in Visual Studio Code. First time, if you have installed the Visual Studio Code extensions, VSCode will install the Pico SDK and then you can click the `Compile` button in the bottom bar.

If you have the cartridge connected via USB, you can use the `Run` button to flash the firmware directly to the cartridge. Another option is to get the UF2 file from the `build` directory, see section [How to get it running quickly](#how-to-get-it-running-quickly).

## Operational framework

### Firmware architecture (Raspberry Pi Pico 2 W)

The firmware executed by the Raspberry Pi Pico 2 W addresses two critical operational roles:

1. **ROM memory emulation**:

    The microcontroller interfaces directly with the SVI-328's cartridge slot to emulate ROM data storage. ROM contents are dynamically allocated and retrieved from the internal memory of the Pico.

The firmware source comprises:

 - `main.c`: Responsible for system initialization, WiFi configuration, and reception and handling of ROM data.
 - `svi-328-cartridge.c/h`: Implements the logic necessary for cartridge ROM emulation.
 - `log.c/h`: Provides logging utilities essential for debugging and real-time data monitoring.

### Hardware design and PCB layout

The project hardware consists of a specialized PCB that integrates the Raspberry Pi Pico W and essential connectors for direct communication with the Spectravideo 328:

 - Edge Connector: Engineered for direct compatibility with the standard SVI-328 cartridge interface.
 - Raspberry Pi Pico W Module: Manages operational logic for ROM emulation and wireless communication protocols.

![SVI-328 PicoROM schematics](images/schematics.png "SVI-328 PicoROM schematics")

## Special thanks

This project is based on [A8PicoCart](https://github.com/robinhedwards/A8PicoCart), [PiCOLECO](https://github.com/aotta/PiCOLECO) and learnings from [SVI-328 MegaROM](https://github.com/fitch/SVI-328-MegaROM).

## License

Detailed licensing information is documented within the included [LICENSE](LICENSE) file.