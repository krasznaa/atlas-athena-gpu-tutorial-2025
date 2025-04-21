// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_CALIBRATEELECTRONS_H
#define CUDAEXAMPLES_CALIBRATEELECTRONS_H

// Framework include(s).
#include "GaudiKernel/StatusCode.h"

// Local include(s).
#include "ElectronDeviceContainer.h"

namespace GPUTutorial
{

   /// Standalone function to calibrate the electrons
   StatusCode calibrateElectrons(ElectronDeviceContainer::const_view input,
                                 ElectronDeviceContainer::view output);

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_CALIBRATEELECTRONS_H
