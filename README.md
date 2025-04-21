# ATLAS Athena GPU Tutorial 2025

This repository collects the code examples used in the 2025 edition of the
GPU programming tutorial of the [ATLAS Experiment](https://atlas.cern/).

## Environment Setup

To set up the recommended build environment for the code in a terminal, please
run:

```sh
source scripts/build_env.sh
```

It just makes sure that `setupATLAS` and `asetup` would be available even in
environments in which they are not defined out of the box, and then set up
a specific version of [Athena](https://gitlab.cern.ch/atlas/athena) for the
tutorial.

If you get an error from the script telling you that
[CUDA](https://developer.nvidia.com/cuda-zone) could not be found, please update
the script to set `CUDA_DIR` to a directory holding a local CUDA installation.
This is needed everywehre outside of the CERN firewall, and even inside of the
fireawall on (most) private laptops.

## Exercises

The exercises are documented in individual Python notebooks. Please open these
to follow the individual exercises.
  - [Exercise 1](01_CUDA_LinearTransform.ipynb): Set up a simple CUDA algorithm,
    debug why it's not working, and fix its memory leaks.
  - [Exercise 2](02_CUDA_xAODCalib.ipynb): Work with a "more realistic" Athena
    algorithm that takes data from, and returns data to an xAOD container.
