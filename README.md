# cutdown_backup

This is baremetal C code for the backup MCU (ATtiny85V) on the high altitude balloon [cutdown controller](https://github.com/dastcvi/cutdown_hardware).

The software is based around SPI commands from the [main MCU](https://github.com/dastcvi/cutdown) to configure it, but once the remove before flight (RBF) plug has been pulled, the backup MCU ignores anything from the main MCU so that it is a redundant device. It also has dissimilar design and separate power conversion to avoid common-mode failures.

Once the RBF plug has been pulled, the backup MCU starts counting down based on the configured timer. Once it reaches zero, it fires the actuator by opening the gate for ten seconds. It's as simple as that. Due to the ten second timing, **the backup can fire either a pyrotechnic squib or thermal cutter with no configuration or software changes**.

## Development Environment
* AtmelStudio 7.0 (other versions may work, but are untested)
* GNU Toolchain for Atmel AVR8 Embedded Processors (https://www.microchip.com/webdoc/AVRLibcReferenceManual/index.html)

## Compiling and Flashing

Compiling and flashing is all done using AtmelStudio and an AVRISP MkII or similar programmer. To plug in the programmer, align the side of the ribbon cable with the red stripe to the side of the connector on the cutdown PCB with pin 1. This connector is the only standard 6-pin (2x3) connector on the board, and it displays `ATTINY_ISP` on the silkscreen.

Open the cutdown project file in AtmelStudio (`cutdown_backup.cproj`). To compile, select `Build -> Build cutdown_backup`. Once the programmer is plugged in and displaying a green light, select `Debug -> Start Without Debugging`. Keep an eye on the bottom of the window to ensure that the software was successfully loaded (there will not be a popup or anything).