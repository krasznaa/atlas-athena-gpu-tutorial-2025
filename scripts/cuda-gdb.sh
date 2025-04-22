#!/bin/bash
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Unset PYTHONHOME, as it messes with cuda-gdb on both Perlmutter and SWAN.
unset PYTHONHOME

# Run cuda-gdb with all the arguments received by the script.
cuda-gdb $@
