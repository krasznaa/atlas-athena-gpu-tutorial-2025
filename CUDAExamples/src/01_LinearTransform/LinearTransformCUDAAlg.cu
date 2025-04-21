// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "LinearTransformCUDAAlg.h"

// CUDA include(s).
#include <cuda_runtime.h>

/// Helper macro for checking CUDA calls
#define ATH_CUDA_CHECK(EXP)                                               \
   do                                                                     \
   {                                                                      \
      const cudaError_t ce = EXP;                                         \
      if (ce != cudaSuccess)                                              \
      {                                                                   \
         ATH_MSG_ERROR("Failed to execute \"" << #EXP << "\" because:"    \
                                              << cudaGetErrorString(ce)); \
         return StatusCode::FAILURE;                                      \
      }                                                                   \
   } while (false)

namespace GPUTutorial
{
   namespace Kernels
   {
      /// Simple kernel for a parallel linear transformation.
      __global__ void linearTransform(std::size_t n, const float *input,
                                      float *output)
      {
         // Stop right away if we're out of bounds.
         const std::size_t i = blockIdx.x * blockDim.x + threadIdx.x;
         if (i >= n) {
            return;
         }

         // Perform a very simple linear transformation.
         output[i] = 2.0f * input[i] + 1.0f;
      }

   } // namespace Kernels

   StatusCode LinearTransformCUDAAlg::initialize()
   {
      // Simply greet the user.
      ATH_MSG_INFO("Initializing " << name() << "...");

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

   StatusCode LinearTransformCUDAAlg::execute(const EventContext &ctx) const
   {
      // Set up an input array on the host.
      constexpr std::size_t n = 1000000;
      std::vector<float> inputHost(n);
      for (std::size_t i = 0; i < n; ++i)
      {
         inputHost[i] = static_cast<float>(i);
      }

      // Allocate input and output buffers on the device.
      float *inputDevice = nullptr;
      float *outputDevice = nullptr;
      ATH_CUDA_CHECK(cudaMalloc(&inputDevice, n * sizeof(float)));
      ATH_CUDA_CHECK(cudaMalloc(&outputDevice, n * sizeof(float)));

      // Copy the input data to the device.
      ATH_CUDA_CHECK(cudaMemcpy(inputDevice, inputHost.data(),
                                n * sizeof(float), cudaMemcpyHostToDevice));

      // Run the kernel.
      const std::size_t blockSize = 256;
      const std::size_t numBlocks = (10000000 + blockSize - 1) / blockSize;
      Kernels::linearTransform<<<numBlocks, blockSize>>>(n, inputDevice,
                                                         outputDevice);
      ATH_CUDA_CHECK(cudaGetLastError());
      ATH_CUDA_CHECK(cudaDeviceSynchronize());

      // Copy the output data back to the host.
      std::vector<float> outputHost(n);
      ATH_CUDA_CHECK(cudaMemcpy(outputHost.data(), outputDevice,
                                n * sizeof(float), cudaMemcpyDeviceToHost));

      // Print some elements of the output.
      ATH_MSG_INFO("outputHost[0]      = " << outputHost[0]);
      ATH_MSG_INFO("outputHost[1000]   = " << outputHost[1000]);
      ATH_MSG_INFO("outputHost[999999] = " << outputHost[999999]);

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace GPUTutorial
