# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(CUDAExamples)

# Check if CUDA is available. If not, skip building the package.
include(CheckLanguage)
check_language(CUDA)
if(NOT CMAKE_CUDA_COMPILER)
   message(STATUS "CUDA not available. Not building package.")
   return()
endif()
