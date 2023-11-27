"""Pykep is a coolbox for interplanetary trajectory design developed by ESA's Advanced Concepts Team. Its main
 purpose is fast prototyping of reseacrh ideas, and is not intended for operational usage.

 Some important conventions followed:
 1 - All units expected are S.I. (m,sec,kg,N) unless explicitly stated.
 2 - The default set of osculating orbital parameters is, in this order: [sma, ecc, incl, W, w, f], where f is the true anomaly
 3 - The default option to represent epochs as floats is the modified julian date 2000 (MJD2000). By default, time durations are in days."""

# Version setup.
from ._version import __version__
del _version

import os as _os

if _os.name == "posix":
    # NOTE: on some platforms Python by default opens extensions
    # with the RTLD_LOCAL flag, which creates problems because
    # public symbols used by heyoka (e.g., sleef functions, quad
    # precision math) are then not found by the LLVM jit machinery.
    # Thus, before importing core, we temporarily flip on the
    # RTLD_GLOBAL flag, which makes the symbols visible and
    # solves these issues. Another possible approach suggested
    # in the llvm discord is to manually and explicitly add
    # libheyoka.so to the DL search path:
    # DynamicLibrarySearchGenerator::Load(“/path/to/libheyoka.so”)
    # See:
    # https://docs.python.org/3/library/ctypes.html
    import ctypes as _ctypes
    import sys as _sys

    _orig_dlopen_flags = _sys.getdlopenflags()
    _sys.setdlopenflags(_orig_dlopen_flags | _ctypes.RTLD_GLOBAL)

    try:
        # Importing cpp functionalities
        from .core import *
        from . import core
    finally:
        # Restore the original dlopen flags whatever
        # happens.
        _sys.setdlopenflags(_orig_dlopen_flags)

        del _ctypes
        del _sys
        del _orig_dlopen_flags
else:
    # Importing cpp functionalities
    from .core import *
    from . import core


del _os

# Importing user defined planets
from . import udpla

# Importing trajectory legs udplas
from . import leg


# Importing the python utils
from .utils import *

# Patch the problem class.
from . import _patch_planet

# Import the plot module
from . import plot

# We import the unit test submodule
from . import test