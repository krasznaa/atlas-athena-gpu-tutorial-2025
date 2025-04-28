#!/usr/bin/env python3
#
# Copyright (C) 2002-2024 CERN for the benefit of the ATLAS collaboration
#

# Core import(s).
from AthenaConfiguration.AllConfigFlags import initConfigFlags
from AthenaConfiguration.ComponentAccumulator import ComponentAccumulator
from AthenaConfiguration.ComponentFactory import CompFactory
from AthenaConfiguration.MainServicesConfig import MainServicesCfg
from AthenaConfiguration.TestDefaults import defaultTestFiles, defaultConditionsTags

# For jets
from JetRecConfig.StandardSmallRJets import AntiKt4EMPFlow
from JetRecConfig.JetRecConfig import JetRecCfg

# I/O import(s).
from AthenaPoolCnvSvc.PoolReadConfig import PoolReadCfg

# System import(s).
import sys

# Need to build the jets here
def JetBuildCfg(flags, **kwargs):
    result = ComponentAccumulator()
    # Setup calorimeter geometry, which is needed for jet reconstruction
    from LArGeoAlgsNV.LArGMConfig import LArGMCfg
    result.merge(LArGMCfg(flags))
    from TileGeoModel.TileGMConfig import TileGMCfg
    result.merge(TileGMCfg(flags))
    # Reconstruct jets
    result.merge(JetRecCfg(flags, AntiKt4EMPFlow))
    return result



def JetPullCUDAAlgCfg(flags, **kwargs):
    # Create an accumulator to hold the configuration.
    result = ComponentAccumulator()
    # Create the example algorithm.
    alg = CompFactory.GPUTutorial.JetPullCUDAAlg(InputContainer="AntiKt4EMPFlowJets", **kwargs)
    result.addEventAlgo(alg)
    # Return the result to the caller.
    return result


if __name__ == '__main__':

    # Set up the job's flags.
    flags = initConfigFlags()
    flags.Exec.MaxEvents = 1000
    #########################################
    flags.Exec.FPE = -2
    flags.Concurrency.NumOffloadThreads = 2
    #########################################
    flags.Input.Files = defaultTestFiles.AOD_RUN3_DATA
    flags.IOVDb.GlobalTag = defaultConditionsTags.RUN3_DATA
    # Ensure MC-based modifiers are removed (!74396)
    flags.Jet.strictMode = False

    flags.fillFromArgs()
    flags.lock()

    # Set up the main services.
    acc = MainServicesCfg(flags)

    # Set up the input file reading.
    acc.merge(PoolReadCfg(flags))

    # Set up jet building
    acc.merge(JetBuildCfg(flags))

    # Set up the tutorial algorithm.
    acc.merge(JetPullCUDAAlgCfg(flags))

    # Run the configuration.
    sys.exit(acc.run().isFailure())
