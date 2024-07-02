# daplink

DAPLink implementation using STM32F103xB.

## Flashing

These instructions work on macOS and are derived from the [DAPLink Developer's Guide](https://github.com/ARMmbed/DAPLink/blob/main/docs/DEVELOPERS-GUIDE.md).

```
git clone https://github.com/ARMmbed/DAPLink.git
cd DAPLink
virtualenv venv
source venv/bin/activate
pip install -r requirements.txt
python tools/progen_compile.py -t make_gcc_arm stm32f103xb_bl stm32f103xb_if
pyocd load -t stm32f103cb projectfiles/make_gcc_arm/stm32f103xb_bl/build/stm32f103xb_bl_crc.bin
cp projectfiles/make_gcc_arm/stm32f103xb_if/build/stm32f103xb_if_crc.bin /Volumes/MAINTENANCE
```

## Revisions

### v1

- copied from https://github.com/berkeleyauv/RoboSub_HW as backup

### v2

- update connector pinout
