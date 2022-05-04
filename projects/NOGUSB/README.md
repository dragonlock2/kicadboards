# NOGUSB

Copied from https://github.com/berkeleyauv/RoboSub_HW as backup.

Board for testing various capabilities of the STM32G0B1 including USB-C PD, USB, bootloaders, and FDCAN. Intended as potential replacement for NOGLINK.

If using the bootloader to program, make sure to unset the nBOOT_SEL before first flash or you will lose access to the bootloader.

## Revisions

### v1.1

- Added connections for DBCC pins, fixing no power on startup
- Rerouted UART pins to a different pair
