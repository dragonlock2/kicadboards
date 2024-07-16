# kicadboards

Hello there! This is the place for all of the little boards that I work on that don't really fit anywhere else. It's also to help open source designs others can reference and I can provide links to.

```
git clone --recursive https://github.com/dragonlock2/kicadboards.git
```

Schematic PDFs are automatically generated and deployed at [matthewtran.dev/kicadboards](https://matthewtran.dev/kicadboards). I recommend [KiCanvas](https://kicanvas.org) for online layout viewing.

## scripts

### diffpair.py

KiCad's calculator doesn't currently include one for a coupled coplanar waveguide with ground ("differential-coplanar" in Altium). Thankfully an open-source solution exists, [atlc](https://atlc.sourceforge.net). Minimal source code for [v4.6.1](https://sourceforge.net/projects/atlc/files/atlc/atlc-4.6.1/) has been added here and the build system has been switched to CMake.

```
cd scripts/external/atlc
mkdir build && cd build
cmake ..
cmake --build .
```
