# NOGPROG

Copied from https://github.com/berkeleyauv/RoboSub_HW as backup.

NOGPROG is a STM32F103CBT6 based DAPLink probe. As a CMSIS-DAP based debugger, it should work with any ARM microcontroller.

## Flashing

Follow the Developers Guide for [DAPLink](https://github.com/ARMmbed/DAPLink) and compile both the `stm32f103xb_bl` and `stm32f103xb_if` projects. Upload the bootloader `stm32f103xb_bl.bin` first (using another debugger) and then NOGPROG should re-enumerate as a `MAINTENANCE` drive. Drag `stm32f103xb_if.bin` into that to install DAPLink.

## Revisions

### v2

- Move to DAPLink
- Added polyfuse and TVS
- Remove target power switch
- Simplify USB re-enumeration circuit
- Add Tag-Connect programming pads
