#!/bin/bash
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Find the directory the script sits in.
SCRIPTDIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

# Command(s) received from the command line.
CMD="$@"

# Run the command using setupATLAS. Need to do it like this to avoid
# passing all command line arguments directly to setupATLAS.
run_cmd() {
   export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
   source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh -c el9 \
      --runtimeOpt="apptainer|--nv" --mount=/opt/nvidia \
      --runpayload="asetup Athena,25.0.29 && ${SCRIPTDIR}/.cmd_perlmutter.sh ${CMD}"
}
run_cmd
