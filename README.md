# cutdown_backup
Code for my work at CU's Laboratory for Atmospheric and Space Physics (LASP).

This is code for the backup MCU (ATtiny85V) on the high altitude balloon 
pyrotechnic cutdown controller that I am designing.

## Development Environment
* AtmelStudio 7.0
* GNU Toolchain for Atmel AVR8 Embedded Processors (https://www.microchip.com/webdoc/AVRLibcReferenceManual/index.html)

## Branching Strategy
The following are the different branches and branch prefixes that should 
be used in this repo
* master: working code to run in the Release build configuration
* debug: working code to run in the Debug build configuration
* feat-: feature branches
* fix-: bug fixes
* test-: tests
In order to preserve branch history, the --no-ff flag should be used when 
merging a feat-, fix-, or test- branch back into debug or master.
