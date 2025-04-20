// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_LINEARTRANSFORMCUDAALG_H
#define CUDAEXAMPLES_LINEARTRANSFORMCUDAALG_H

// Framework include(s).
#include "AthenaBaseComps/AthReentrantAlgorithm.h"

namespace GPUTutorial
{
   /// Example algorithm showing the simplest use of CUDA in Athena
   class LinearTransformCUDAAlg final : public AthReentrantAlgorithm
   {
   public:
      /// Use the base class's constructor(s).
      using AthReentrantAlgorithm::AthReentrantAlgorithm;

      /// @name Functions inherited from @c AthReentrantAlgorithm
      /// @{

      /// Function initializing the algorithm
      virtual StatusCode initialize() override;
      /// Function executing the algorithm
      virtual StatusCode execute(const EventContext &ctx) const override;

      /// @}

   }; // class LinearTransformCUDAAlg

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_LINEARTRANSFORMCUDAALG_H
