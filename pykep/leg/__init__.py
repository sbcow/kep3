## Copyright 2023, 2024 Dario Izzo (dario.izzo@gmail.com), Francesco Biscani
## (bluescarni@gmail.com)## 
## This file is part of the kep3 library.## 
## This Source Code Form is subject to the terms of the Mozilla
## Public License v. 2.0. If a copy of the MPL was not distributed
## with this file, You can obtain one at http://mozilla.org/MPL/2.0/.

"""
Various types of interplanetary trajectory legs
"""
from .. import core as _core

# Renaming cpp legs (we need to create an alias first and then 
# to fool sphinx into thinking these are not aliases, else the sphinx built docs
# would report them as aliases and fail to document these classes)
sims_flanagan = _core._sims_flanagan
sims_flanagan.__name__ = "sims_flanagan"
sims_flanagan.__module__ = "leg"

# Removing core from the list of imported symbols.
del _core
