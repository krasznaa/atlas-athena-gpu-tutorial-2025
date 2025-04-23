# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Clean out the environment as a first step.
unset CMAKE_PREFIX_PATH
unset ROOTSYS

# Set up ALRB.
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh

# Set up Athena-25.0.29.
asetup Athena,25.0.29

# Set up the oneAPI compilers.
source /cvmfs/projects.cern.ch/intelsw/oneAPI/linux/x86_64/2024/compiler/2024.1/env/vars.sh --include-intel-llvm
export CC=`which clang`
export CXX=`which clang++`
export SYCLCXX="${CXX}"
export SYCLFLAGS="-fsycl"
