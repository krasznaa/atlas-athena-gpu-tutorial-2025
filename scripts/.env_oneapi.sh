# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Clean out the environment as a first step.
unset CMAKE_PREFIX_PATH
unset ROOTSYS

# Set up ALRB.
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh

# Set up Athena-25.0.29.
asetup Athena,25.0.29

# Set up the oneAPI.
ONEAPI_ROOT=${ONEAPI_ROOT:-"/home/krasznaa/software/intel/oneapi-2025.1.0"}
source "${ONEAPI_ROOT}/setvars.sh" --include-intel-llvm
unset TBBROOT
unset CPATH
export CC=`which clang`
export CXX=`which clang++`
export SYCLCXX="${CXX}"
export SYCLFLAGS="-fsycl"
