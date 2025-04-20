#!/usr/bin/env python3
#
# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#

# Core import(s).
from AthenaConfiguration.AllConfigFlags import initConfigFlags
from AthenaConfiguration.ComponentAccumulator import ComponentAccumulator
from AthenaConfiguration.ComponentFactory import CompFactory
from AthenaConfiguration.MainServicesConfig import MainServicesCfg

# System import(s).
import sys

def LinearTransformCUDAAlgCfg(flags, **kwargs):
   # Create an accumulator to hold the configuration.
   result = ComponentAccumulator()
   # Create the example algorithm.
   alg = CompFactory.GPUTutorial.LinearTransformCUDAAlg(**kwargs)
   result.addEventAlgo(alg)
   # Return the result to the caller.
   return result

if __name__ == '__main__':

   # Set up the job's flags.
   flags = initConfigFlags()
   flags.Exec.MaxEvents = 100
   flags.fillFromArgs()
   flags.lock()

   # Set up the main services.
   acc = MainServicesCfg(flags)

   # Set up the tutorial algorithm.
   acc.merge(LinearTransformCUDAAlgCfg(flags))

   # Run the configuration.
   sys.exit(acc.run().isFailure())
