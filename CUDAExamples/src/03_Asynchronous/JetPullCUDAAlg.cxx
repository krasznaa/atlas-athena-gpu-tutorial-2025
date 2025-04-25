// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

// Local include(s).
#include "JetPullCUDAAlg.h"

// Framework include(s).
#include "StoreGate/ReadHandle.h"
#include "StoreGate/WriteHandle.h"
#include "xAODCore/AuxContainerBase.h"
#include "xAODCore/ShallowCopy.h"
#include "xAODJet/JetContainer.h"
#include "xAODJet/Jet.h"

// VecMem include(s).
#include <vecmem/memory/cuda/host_memory_resource.hpp>
// #include <vecmem/memory/cuda/device_memory_resource.hpp>
#include <vecmem/memory/pool_memory_resource.hpp>
#include <vecmem/memory/synchronized_memory_resource.hpp>
#include <vecmem/utils/cuda/copy.hpp>

// STL includes(s)
#include <format>
#include <span>
#include <vector>

namespace GPUTutorial
{
   struct JetPullCUDAAlg::MemoryResources
   {
      /// Uncached host memory resource
      vecmem::cuda::host_memory_resource m_plainHostMR;
      /// Cached host memory resource
      vecmem::pool_memory_resource m_cachedHostMR{m_plainHostMR};
      /// Synchronized and cached host memory resource
      vecmem::synchronized_memory_resource m_hostMR{m_cachedHostMR};

      std::pmr::memory_resource* hostMR();
   };

   std::pmr::memory_resource* JetPullCUDAAlg::MemoryResources::hostMR() {
      return &m_hostMR;
   }

   JetPullCUDAAlg::JetPullCUDAAlg(const std::string &name,
                                              ISvcLocator *svcloc)
       : AthAsynchronousAlgorithm(name, svcloc) {}

   JetPullCUDAAlg::~JetPullCUDAAlg() = default;

   StatusCode JetPullCUDAAlg::initialize()
   {
      // Set up the memory resources.
      m_memoryResources = std::make_unique<MemoryResources>();

      // Set up the input and output keys.
      ATH_CHECK(m_inputKey.initialize());
      ATH_CHECK(m_outputKey.initialize());

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

   StatusCode JetPullCUDAAlg::execute(const EventContext &ctx) const
   {
      // Get the input container.
      SG::ReadHandle inputJets(m_inputKey, ctx);

      // Collect required data on the host:
      //    - Number of jets
      //    - Number of constituents of each jet
      //    - pt, eta, phi for jets
      //    - pt, eta, phi for constituents
      std::size_t nJets = inputJets->size();
      if (nJets == 0) {
         return StatusCode::SUCCESS;
      }
      std::pmr::vector<std::size_t> nConstituents(m_memoryResources->hostMR());
      // // Is this worth it?
      // std::pmr::vector<float> jetPt(nJets, m_memoryResources->hostMR());
      // std::pmr::vector<float> jetEta(nJets, m_memoryResources->hostMR());
      // std::pmr::vector<float> jetPhi(nJets, m_memoryResources->hostMR());
      std::pmr::vector<float> constPt(m_memoryResources->hostMR());
      std::pmr::vector<float> constEta(m_memoryResources->hostMR());
      std::pmr::vector<float> constPhi(m_memoryResources->hostMR());

      // Get jet data
      static const SG::AuxElement::ConstAccessor<float> ptAcc("pt");
      static const SG::AuxElement::ConstAccessor<float> etaAcc("eta");
      static const SG::AuxElement::ConstAccessor<float> phiAcc("phi");
      std::span<const float> jetPt(ptAcc.getDataArray(*inputJets), nJets);
      std::span<const float> jetEta(etaAcc.getDataArray(*inputJets), nJets);
      std::span<const float> jetPhi(phiAcc.getDataArray(*inputJets), nJets);
      // std::memcpy(jetPt.data(), ptAcc.getDataArray(*inputJets), nJets * sizeof(float));
      // std::memcpy(jetEta.data(), etaAcc.getDataArray(*inputJets), nJets * sizeof(float));
      // std::memcpy(jetPhi.data(), phiAcc.getDataArray(*inputJets), nJets * sizeof(float));

      // Get constituent data. We loop twice so we can allocate the constituent arrays in one go.
      std::size_t totalConstituents = 0;
      nConstituents.reserve(nJets);
      for (const auto& jet : *inputJets) {
         std::size_t nConst = jet->numConstituents();
         totalConstituents += nConst;
         nConstituents.push_back(nConst);
      }
      
      constPt.reserve(totalConstituents);
      constEta.reserve(totalConstituents);
      constPhi.reserve(totalConstituents);
      for (const auto& jet : *inputJets) {
         for (const auto* c : jet->getConstituents()) {
            constPt.push_back(c->pt());
            constEta.push_back(c->eta());
            constPhi.push_back(c->phi());
         }
      }
   
      ATH_MSG_INFO(std::format("Read {0} jets with eta[0,{0} -1] [{1},{2}] and {3} nConstituents[0,{0} -1] [{4},{5}]",
                  nJets, jetEta[0], jetEta[nJets - 1], totalConstituents, nConstituents[0], nConstituents[nJets - 1]));

      // Create host buffers to store results
      std::pmr::vector<float> jetPullY(nJets, m_memoryResources->hostMR());
      std::pmr::vector<float> jetPullPhi(nJets, m_memoryResources->hostMR());

      // Run GPU code
      ATH_CHECK(device_execute(jetPt, jetEta, jetPhi, nConstituents, constPt, constEta, constPhi,
                               jetPullY, jetPullPhi));
      
      // Save output
      // Get an std::pair of unique_ptrs back
      auto outputJetsSC = xAOD::shallowCopyContainer(*inputJets, ctx);
      auto&& [outputJets, outputAux] = outputJetsSC;

      // Record
      SG::WriteHandle output(m_outputKey, ctx);
      ATH_CHECK(output.record(std::move(outputJets), std::move(outputAux)));

      // Return gracefully.
      return StatusCode::SUCCESS;
   }

} // namespace GPUTutorial
