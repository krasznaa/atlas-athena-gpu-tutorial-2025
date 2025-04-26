// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_LINEARTRANSFORMSYCLALG_H
#define CUDAEXAMPLES_LINEARTRANSFORMSYCLALG_H

// Framework include(s).
#include "AthenaBaseComps/AthReentrantAlgorithm.h"

namespace GPUTutorial
{
   /// Example algorithm showing the simplest use of SYCL in Athena
   class LinearTransformSYCLAlg final : public AthReentrantAlgorithm
   {
   public:
      /// Use the base class's constructor(s).
      using AthReentrantAlgorithm::AthReentrantAlgorithm;

      /// @name Functions inherited from @c AthReentrantAlgorithm
      /// @{

      /// Function initializing the algorithm
      StatusCode initialize() override;
      /// Function executing the algorithm
      StatusCode execute(const EventContext &ctx) const override;

      /// @}

   }; // class LinearTransformSYCLAlg

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_LINEARTRANSFORMSYCLALG_H
