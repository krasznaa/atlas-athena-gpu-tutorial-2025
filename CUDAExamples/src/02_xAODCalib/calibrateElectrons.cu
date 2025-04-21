// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "calibrateElectrons.h"

// Framework include(s).
#include "AthenaKernel/errorcheck.h"

/// Helper macro for checking CUDA calls
#define ATH_CUDA_CHECK(EXP)                                           \
   do                                                                 \
   {                                                                  \
      const cudaError_t ce = EXP;                                     \
      if (ce != cudaSuccess)                                          \
      {                                                               \
         REPORT_ERROR_WITH_CONTEXT(StatusCode::FAILURE,               \
                                   "GPUTutorial::calibrateElectrons") \
             << "Failed to execute \""                                \
             << #EXP << "\" because:"                                 \
             << cudaGetErrorString(ce);                               \
         return StatusCode::FAILURE;                                  \
      }                                                               \
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

   StatusCode calibrateElectrons(ElectronDeviceContainer::const_view input,
                                 ElectronDeviceContainer::view output)
   {
      // Launch the kernel.
      const int blockSize = 256;
      const int numBlocks = (input.capacity() + blockSize - 1) / blockSize;
      Kernels::calibrateElectrons<<<numBlocks, blockSize>>>(input, output);

      // Check for errors in kernel launch.
      ATH_CUDA_CHECK(cudaGetLastError());

      // Wait for the device to finish with the kernel.
      ATH_CUDA_CHECK(cudaDeviceSynchronize());

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace GPUTutorial
