#!/bin/bash
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Find the directory the script sits in.
SCRIPTDIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

# Set up an interactive environment using setupATLAS.
start_env() {
   export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
   source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh -c el9 \
      --runtimeOpt="apptainer|--nv" --runtimeOpt="singularity|--nv" \
      --runtimeOpt="docker|--gpus all" --runtimeOpt="podman| --gpus all" \
      --mount=/opt/nvidia:/opt/nvidia \
      --postsetup="asetup Athena,25.0.29 && source ${SCRIPTDIR}/.env_perlmutter.sh"
}
start_env
