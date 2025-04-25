// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "JetPullCUDAAlg.h"

// Framework include(s).
#include "AthenaKernel/errorcheck.h"

/// Helper macro for checking CUDA calls
#define ATH_CUDA_CHECK(EXP)                                             \
   do                                                                   \
   {                                                                    \
      const cudaError_t ce = EXP;                                       \
      if (ce != cudaSuccess)                                            \
      {                                                                 \
         REPORT_ERROR_WITH_CONTEXT(StatusCode::FAILURE,                 \
                                   "GPUTutorial::JetPullCUDAAlg")       \
             << "Failed to execute \""                                  \
             << #EXP << "\" :"                                          \
             << cudaGetErrorName(ce) << ": " << cudaGetErrorString(ce); \
         return StatusCode::FAILURE;                                    \
      }                                                                 \
   } while (false)

namespace GPUTutorial
{
   namespace Kernels
   {
      /// Simple kernel "calibrating" electrons
      __global__ void
      calibrateElectrons(ElectronDeviceContainer::const_view inputView,
                         ElectronDeviceContainer::view outputView)
      {
         // Get the index of the current thread.
         const int idx = blockIdx.x * blockDim.x + threadIdx.x;

         // Construct the device containers.
         const ElectronDeviceContainer::const_device input(inputView);
         ElectronDeviceContainer::device output(outputView);

         // Check if the index is within bounds.
         if (idx >= input.size())
         {
            return;
         }

         // Copy the input electron to the output container.
         output[idx].eta() = input[idx].eta();
         output[idx].phi() = input[idx].phi();

         // Perform some calibration on the output electron.
      }

   } // namespace Kernels

   StatusCode JetPullCUDAAlg::deviceExecute(const std::span<const float>& jetPt, ///< [in] Jet pT array
                                            const std::span<const float>& jetEta, ///< [in] Jet eta array
                                            const std::span<const float>& jetPhi, ///< [in] jet phi array
                                            const std::pmr::vector<std::size_t>& nConstituents, ///< [in] number of constituents for each jet
                                            const std::pmr::vector<float>& constPt, ///< [in] flat array of constituent pTs (grouped by jet)
                                            const std::pmr::vector<float>& constEta, ///< [in] flat array of constituent etas (grouped by jet)
                                            const std::pmr::vector<float>& constPhi, ///< [in] flat array of constituent phis (grouped by jet)
                                            std::pmr::vector<float>& jetPullY, ///< [out] rapidity component of each jet pull vector
                                            std::pmr::vector<float>& jetPullPhi ///< [out] phi component of each jet pull vector
                                          ) const
   {
      
   }

} // namespace GPUTutorial
