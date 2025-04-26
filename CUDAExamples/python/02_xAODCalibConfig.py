#!/usr/bin/env python3
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Core import(s).
from AthenaConfiguration.AllConfigFlags import initConfigFlags
from AthenaConfiguration.ComponentAccumulator import ComponentAccumulator
from AthenaConfiguration.ComponentFactory import CompFactory
from AthenaConfiguration.MainServicesConfig import MainServicesCfg
from AthenaConfiguration.TestDefaults import defaultTestFiles

# I/O import(s).
from AthenaPoolCnvSvc.PoolReadConfig import PoolReadCfg

# System import(s).
import sys


def ElectronCalibCUDAAlgCfg(flags, **kwargs):
    # Create an accumulator to hold the configuration.
    result = ComponentAccumulator()
    # Create the example algorithm.
    alg = CompFactory.GPUTutorial.ElectronCalibCUDAAlg(**kwargs)
    result.addEventAlgo(alg)
    # Return the result to the caller.
    return result


if __name__ == '__main__':

    # Set up the job's flags.
    flags = initConfigFlags()
    flags.Exec.MaxEvents = 1000
    flags.Input.Files = defaultTestFiles.AOD_RUN3_DATA
    flags.fillFromArgs()
    flags.lock()

    # Set up the main services.
    acc = MainServicesCfg(flags)

    # Set up the input file reading.
    acc.merge(PoolReadCfg(flags))

    # Set up the tutorial algorithm.
    acc.merge(ElectronCalibCUDAAlgCfg(flags))

    # Run the configuration.
    sys.exit(acc.run().isFailure())
