// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_ELECTRONCALIBCUDAALG_H
#define CUDAEXAMPLES_ELECTRONCALIBCUDAALG_H

// Framework include(s).
#include "AthenaBaseComps/AthReentrantAlgorithm.h"
#include "StoreGate/ReadHandleKey.h"
#include "StoreGate/WriteHandleKey.h"
#include "xAODEgamma/ElectronContainer.h"

// System include(s).
#include <memory>

namespace GPUTutorial
{
   /// Example algorithm performing a calibration on xAOD::Electron objects
   class ElectronCalibCUDAAlg final : public AthReentrantAlgorithm
   {
   public:
      /// Constructor
      ElectronCalibCUDAAlg(const std::string &name, ISvcLocator *svcloc);
      /// Destructor
      ~ElectronCalibCUDAAlg() override;

      /// @name Functions inherited from @c AthReentrantAlgorithm
      /// @{

      /// Function initializing the algorithm
      StatusCode initialize() override;
      /// Function executing the algorithm
      StatusCode execute(const EventContext &ctx) const override;

      /// @}

   private:
      /// @name Algorithm properties
      /// @{

      /// The input container key
      SG::ReadHandleKey<xAOD::ElectronContainer> m_inputKey{
          this, "InputContainer", "Electrons",
          "The input electron container"};
      /// The output container key
      SG::WriteHandleKey<xAOD::ElectronContainer> m_outputKey{
          this, "OutputContainer", "CalibratedElectrons",
          "The output electron container"};

      /// @}

      /// @name Algorithm data members
      /// @{

      /// PIMPL structure of memory resources
      struct MemoryResources;
      /// Memory resources used by the algorithm
      std::unique_ptr<MemoryResources> m_memoryResources;

      /// @}

   }; // class ElectronCalibCUDAAlg

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_ELECTRONCALIBCUDAALG_H
