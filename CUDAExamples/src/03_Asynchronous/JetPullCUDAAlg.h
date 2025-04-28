// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_JETPULLCUDAALG_H
#define CUDAEXAMPLES_JETPULLCUDAALG_H

// Framework include(s).
#include "AthenaBaseComps/AthAsynchronousAlgorithm.h"
#include "StoreGate/ReadHandleKey.h"
#include "StoreGate/WriteHandleKey.h"
#include "xAODJet/JetContainer.h"

// System include(s).
#include <memory>
#include <span>
#include <vector>

namespace GPUTutorial
{
   /// Example algorithm performing a calibration on xAOD::Electron objects
   class JetPullCUDAAlg final : public AthAsynchronousAlgorithm
   {
   public:
      /// Constructor
      JetPullCUDAAlg(const std::string &name, ISvcLocator *svcloc);
      /// Destructor
      ~JetPullCUDAAlg() override;


      /// Entry point to CUDA portion
      StatusCode deviceExecute(const std::span<const float>& jetPt, ///< [in] Jet pT array
                               const std::span<const float>& jetEta, ///< [in] Jet eta array
                               const std::span<const float>& jetPhi, ///< [in] jet phi array
                               const std::pmr::vector<std::size_t>& nConstituents, ///< [in] number of constituents for each jet
                               const std::pmr::vector<float>& constPt, ///< [in] flat array of constituent pTs (grouped by jet)
                               const std::pmr::vector<float>& constEta, ///< [in] flat array of constituent etas (grouped by jet)
                               const std::pmr::vector<float>& constPhi, ///< [in] flat array of constituent phis (grouped by jet)
                               std::pmr::vector<float>& jetPullEta, ///< [out] eta component of each jet pull vector
                               std::pmr::vector<float>& jetPullPhi ///< [out] phi component of each jet pull vector
                              ) const;

      /// @name Functions inherited from @c AthAsynchronousAlgorithm
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
      SG::ReadHandleKey<xAOD::JetContainer> m_inputKey{
          this, "InputContainer", "AntiKt4EMPFlowJets",
          "The input jet container"};
      /// The output container key
      SG::WriteHandleKey<xAOD::JetContainer> m_outputKey{
          this, "OutputContainer", "JetsWithPull",
          "The output jet container with pull vectors"};
      /// Pull angle matrix -- on device
      // SG::WriteHandleKey<double*> m_outputKey{
      //     this, "OutputContainer", "JetPullMatrix",
      //     "The output jet container with pull vectors"};
      /// @}

      /// @name Algorithm data members
      /// @{

      /// PIMPL structure of memory resources
      struct MemoryResources;
      /// Memory resources used by the algorithm
      std::unique_ptr<MemoryResources> m_memoryResources;

      /// @}
   }; // class JetPullCUDAAlg

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_JETPULLCUDAALG_H
