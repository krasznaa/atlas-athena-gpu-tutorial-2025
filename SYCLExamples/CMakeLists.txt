# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Set the name of the package.
atlas_subdir(SYCLExamples)

# Find the required packages.
find_package(vecmem)

# Look for a valid SYCL compiler.
include("${vecmem_LANGUAGE_FILE}")
vecmem_check_language(SYCL)
if(NOT CMAKE_SYCL_COMPILER)
   message(STATUS "SYCL not available. Not building package.")
   return()
endif()
enable_language(SYCL)

# Component(s) in the package.
atlas_add_component(SYCLExamples
   src/*/*.h src/*/*.cxx src/*/*.sycl
   LINK_LIBRARIES vecmem::core AthenaBaseComps)

# Install files from the package.
atlas_install_python_modules(python/*.py)
