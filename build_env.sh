# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Set up ALRB.
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh

# Set up Athena-25.0.29.
asetup Athena,25.0.29

# Set up CUDA from CVMFS.
CUDA_DIR="/cvmfs/projects.cern.ch/lcg/releases/cuda/12.8/`uname -m`-linux"
if [ -d "${CUDA_DIR}" ]; then
   export PATH="${CUDA_DIR}/bin"${PATH:+:${PATH}}
   export LD_LIBRARY_PATH="${CUDA_DIR}/lib64:${CUDA_DIR}/extras/CUPTI/lib64$"{LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
   export CUDACXX=`which nvcc`
   echo "Configured CUDA from: ${CUDA_DIR}"
else
   echo "WARNING:"
   echo "WARNING: CUDA not available from CVMFS. Please set it up by hand!"
   echo "WARNING:"
fi
