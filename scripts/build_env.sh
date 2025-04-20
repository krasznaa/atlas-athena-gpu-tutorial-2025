# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#
# Script setting up the build environment for the tutorial.
#

# Set up ALRB.
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh

# Set up Athena-25.0.29.
asetup Athena,25.0.29

# Check if CUDA is available.
if [ ! -f "${CUDACXX}" ]; then

   # Directory to set up CUDA from.
   CUDA_DIR="/your/path/to/cuda"

   # (Try to) Set up CUDA.
   if [ ! -d "${CUDA_DIR}" ]; then
      echo "ERROR:"
      echo "ERROR: CUDA not available. Please configure the setup script!"
      echo "ERROR:"
      exit 1
   else
      export CMAKE_PREFIX_PATH="${CUDA_DIR}"${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
      export PATH="${CUDA_DIR}/bin"${PATH:+:${PATH}}
      export LD_LIBRARY_PATH="${CUDA_DIR}/lib64"{LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
      export CUDACXX=`which nvcc`
   fi
fi
