// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "ElectronCalibCUDAAlg.h"
#include "ElectronDeviceContainer.h"
#include "calibrateElectrons.h"

// Framework include(s).
#include "AthContainers/tools/copyAuxStoreThinned.h"
#include "StoreGate/ReadHandle.h"
#include "StoreGate/WriteHandle.h"
#include "xAODCore/AuxContainerBase.h"

// VecMem include(s).
#include <vecmem/memory/cuda/host_memory_resource.hpp>
#include <vecmem/memory/cuda/device_memory_resource.hpp>
#include <vecmem/memory/pool_memory_resource.hpp>
#include <vecmem/memory/synchronized_memory_resource.hpp>
#include <vecmem/utils/cuda/copy.hpp>

namespace GPUTutorial
{

   struct ElectronCalibCUDAAlg::MemoryResources
   {
      /// Uncached host memory resource
      vecmem::cuda::host_memory_resource m_hostMR;
      /// Cached host memory resource
      vecmem::pool_memory_resource m_cachedHostMR{m_hostMR};
      /// Synchronized and cached host memory resource
      vecmem::synchronized_memory_resource m_syncHostMR{m_cachedHostMR};

      /// Uncached device memory resource
      vecmem::cuda::device_memory_resource m_deviceMR;
      /// Cached device memory resource
      vecmem::pool_memory_resource m_cachedDeviceMR{m_deviceMR};
      /// Synchronized and cached device memory resource
      vecmem::synchronized_memory_resource m_syncDeviceMR{m_cachedDeviceMR};
   };

   ElectronCalibCUDAAlg::ElectronCalibCUDAAlg(const std::string &name,
                                              ISvcLocator *svcloc)
       : AthReentrantAlgorithm(name, svcloc) {}

   ElectronCalibCUDAAlg::~ElectronCalibCUDAAlg() = default;

   StatusCode ElectronCalibCUDAAlg::initialize()
   {
      // Set up the memory resources.
      m_memoryResources = std::make_unique<MemoryResources>();

      // Set up the input and output keys.
      ATH_CHECK(m_inputKey.initialize());
      ATH_CHECK(m_outputKey.initialize());

      // Return gracefuilly.
      return StatusCode::SUCCESS;
   }

   StatusCode ElectronCalibCUDAAlg::execute(const EventContext &ctx) const
   {
      // Get the input container.
      SG::ReadHandle input(m_inputKey, ctx);

      // Set up a host buffer for the electron container.
      auto nElectrons = static_cast<ElectronDeviceContainer::buffer::size_type>(
          input->size());
      ElectronDeviceContainer::buffer
          hostBuffer{nElectrons, m_memoryResources->m_syncHostMR};

      // Copy data from the xAOD container into the host buffer.
      static const SG::AuxElement::ConstAccessor<float> etaAcc("eta");
      static const SG::AuxElement::ConstAccessor<float> phiAcc("phi");
      std::memcpy(hostBuffer.get<0>().ptr(), etaAcc.getDataArray(*input),
                  nElectrons * sizeof(float));
      std::memcpy(hostBuffer.get<1>().ptr(), phiAcc.getDataArray(*input),
                  nElectrons * sizeof(float));

      // Helper object used to copy data between the host and the device.
      vecmem::cuda::copy copy;

      // Create two device buffers.
      ElectronDeviceContainer::buffer deviceInputBuffer{
          nElectrons, m_memoryResources->m_cachedDeviceMR};
      copy.setup(deviceInputBuffer)->wait();
      ElectronDeviceContainer::buffer deviceOutputBuffer{
          nElectrons, m_memoryResources->m_cachedDeviceMR};
      copy.setup(deviceOutputBuffer)->wait();

      // Copy data into the input buffer.
      copy(hostBuffer, deviceInputBuffer)->wait();

      // Run the GPU calibration in a separate function.
      ATH_CHECK(calibrateElectrons(deviceInputBuffer, deviceOutputBuffer));

      // Copy the output buffer back to the host.
      copy(deviceOutputBuffer, hostBuffer)->wait();

      // Construct the output container.
      auto outputAux = std::make_unique<xAOD::AuxContainerBase>();
      SG::copyAuxStoreThinned(*(input->getConstStore()), *outputAux, nullptr);
      std::memcpy(outputAux->getData(etaAcc.auxid(), nElectrons, nElectrons),
                  hostBuffer.get<0>().ptr(), nElectrons * sizeof(float));
      std::memcpy(outputAux->getData(phiAcc.auxid(), nElectrons, nElectrons),
                  hostBuffer.get<1>().ptr(), nElectrons * sizeof(float));
      auto outputInterface = std::make_unique<xAOD::ElectronContainer>();
      for (std::size_t i = 0; i < nElectrons; ++i)
      {
         outputInterface->push_back(new xAOD::Electron());
      }
      outputInterface->setStore(outputAux.get());

      // Record the output container(s).
      SG::WriteHandle output(m_outputKey, ctx);
      ATH_CHECK(output.record(std::move(outputInterface),
                              std::move(outputAux)));

      // Return gracefuilly.
      return StatusCode::SUCCESS;
   }

} // namespace GPUTutorial
