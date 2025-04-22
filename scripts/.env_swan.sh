# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Clean out the environment as a first step.
unset CMAKE_PREFIX_PATH
unset ROOTSYS

# Set up ALRB.
export ATLAS_LOCAL_ROOT_BASE=/cvmfs/atlas.cern.ch/repo/ATLASLocalRootBase
source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh

# Set up Athena-25.0.29.
asetup Athena,25.0.29
