#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Make CUDA available.
export CMAKE_PREFIX_PATH="/opt/nvidia/hpc_sdk/Linux_x86_64/24.5/cuda/12.4"${CMAKE_PREFIX_PATH:+:${CMAKE_PREFIX_PATH}}
export PATH="/opt/nvidia/hpc_sdk/Linux_x86_64/24.5/compilers/bin/:"${PATH:+:${PATH}}
export LD_LIBRARY_PATH="/opt/nvidia/hpc_sdk/Linux_x86_64/24.5/cuda/12.4/lib64:/opt/nvidia/hpc_sdk/Linux_x86_64/24.5/compilers/lib"${LD_LIBRARY_PATH:+:${LD_LIBRARY_PATH}}
export CUDACXX=`which nvcc`
