import subprocess
import tempfile
import time
from pathlib import Path

# all in mm
TRACE_WIDTH = 0.25
TRACE_GAP   = None
POUR_GAP    = None
PROCESS     = "OSHPark 4 Layer Outer"
QUALITY     = "8"  # increase until no difference or 8

"""
Precomputed dimensions are listed as <width>, with gap using minimum space. For dimensions
called gap, use minimum trace width. Use minimum space copper pour.

OSHPark 2 Layer
-  90Ω: 0.45mm
- 100Ω: 0.31mm
- 120Ω: 0.16mm

OSHPark 4 Layer Outer
-  90Ω: 0.25mm
- 100Ω: 0.19mm
- 120Ω: 0.16mm gap
"""

PROCESSES = {
    "OSHPark 2 Layer": {
        "minimum_trace"          : 0.1524,
        "minimum_space"          : 0.1524,
        "dielectric_thickness"   : 1.5240,
        "trace_thickness"        : 0.0356,
        "dielectric_permittivity": 4.5,
    },
    "OSHPark 4 Layer Outer": {
        "minimum_trace"          : 0.1270,
        "minimum_space"          : 0.1270,
        "dielectric_thickness"   : 0.2021,
        "trace_thickness"        : 0.0432, # outer layer
        "dielectric_permittivity": 3.61,
    },
}

if __name__ == "__main__":
    p = PROCESSES[PROCESS]
    if TRACE_WIDTH is None:
        TRACE_WIDTH = p["minimum_trace"]
    if TRACE_GAP is None:
        TRACE_GAP = p["minimum_space"]
    if POUR_GAP is None:
        POUR_GAP = p["minimum_space"]
    assert(TRACE_WIDTH >= p["minimum_trace"])
    assert(TRACE_GAP   >= p["minimum_space"])
    assert(POUR_GAP    >= p["minimum_space"])
    with tempfile.TemporaryDirectory() as tmpdir:
        start = time.time()
        subprocess.run([Path(__file__).parent / "external/atlc/build/create_bmp_for_microstrip_coupler",
            "-b", QUALITY,
            str(TRACE_WIDTH),
            str(TRACE_GAP),
            str(POUR_GAP),
            str(p["dielectric_thickness"]),
            str(p["trace_thickness"]),
            "1.0",
            str(p["dielectric_permittivity"]),
            "out.bmp"
        ], cwd=tmpdir)
        subprocess.run([Path(__file__).parent / "external/atlc/build/atlc",
            "-d", f"0xac82ac={p['dielectric_permittivity']}",
            "out.bmp"
        ], cwd=tmpdir) # use Zdiff for differential impedance
        print(f"done! took {time.time() - start:.1f}s")
