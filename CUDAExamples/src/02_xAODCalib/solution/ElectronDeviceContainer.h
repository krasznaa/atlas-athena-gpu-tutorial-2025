// Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#ifndef CUDAEXAMPLES_ELECTRONDEVICECONTAINER_H
#define CUDAEXAMPLES_ELECTRONDEVICECONTAINER_H

// VecMem include(s).
#include <vecmem/edm/container.hpp>

namespace GPUTutorial
{
   /// Interface for the VecMem based GPU friendly ElectronDeviceContainer.
   template <typename BASE>
   struct ElectronDeviceInterface : public BASE
   {
      /// Inherit the base class's constructor(s)
      using BASE::BASE;

      /// Inherit the base class's assignment operator(s)
      using BASE::operator=;

      /// Get the pseudorapidity of the electrons (const)
      VECMEM_HOST_AND_DEVICE
      const auto &eta() const { return BASE::template get<0>(); }
      /// Get the pseudorapidity of the electrons (non-const)
      VECMEM_HOST_AND_DEVICE
      auto &eta() { return BASE::template get<0>(); }

      /// Get the azimuthal angles of the electrons (const)
      VECMEM_HOST_AND_DEVICE
      const auto &phi() const { return BASE::template get<1>(); }
      /// Get the azimuthal angles of the electrons (non-const)
      VECMEM_HOST_AND_DEVICE
      auto &phi() { return BASE::template get<1>(); }

      // FIX

      /// Get the transverse momentum of the electrons (const)
      VECMEM_HOST_AND_DEVICE
      const auto &pt() const { return BASE::template get<2>(); }
      /// Get the transverse momentum of the electrons (non-const)
      VECMEM_HOST_AND_DEVICE
      auto &pt() { return BASE::template get<2>(); }

      /// Get the author of the electrons (const)
      VECMEM_HOST_AND_DEVICE
      const auto &author() const { return BASE::template get<3>(); }
      /// Get the author of the electrons (non-const)
      VECMEM_HOST_AND_DEVICE
      auto &author() { return BASE::template get<3>(); }

      // FIX

   }; // struct ElectronDeviceInterface

   /// SoA, GPU friendly electron container.
   using ElectronDeviceContainer = vecmem::edm::container<
       ElectronDeviceInterface, vecmem::edm::type::vector<float>,
       vecmem::edm::type::vector<float>,
       // FIX
       vecmem::edm::type::vector<float>,
       vecmem::edm::type::vector<std::uint16_t>
       // FIX
       >;

} // namespace GPUTutorial

#endif // CUDAEXAMPLES_ELECTRONDEVICECONTAINER_H
