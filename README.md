# ATLAS Athena GPU Tutorial 2025

This repository collects the code examples used in the 2025 edition of the
GPU programming tutorial of the [ATLAS Experiment](https://atlas.cern/).

## Environment

The exercises are primarily meant to be run on the
[NERSC Perlmutter Supercomputer](https://docs.nersc.gov/systems/perlmutter/architecture/),
using its [Jupyter notebook interface](https://jupyter.nersc.gov/).

Another option is to make use of
[CERN's SWAN infrastructure](https://swan.cern.ch/). As long as you have a
CERN account, you could open the repository on SWAN using
[this link](https://cern.ch/swanserver/cgi-bin/go/?projurl=https://github.com/krasznaa/atlas-athena-gpu-tutorial-2025.git).

It is also an excellent option to use the code on a private machine, using
[VSCode](https://code.visualstudio.com/). Without much explanation, you need:
  - A [RHEL 9](https://docs.redhat.com/fr/documentation/red_hat_enterprise_linux/9)
    compatible OS ([WSL](https://learn.microsoft.com/en-us/windows/wsl/install)
    can work very nicely with
    [AlmaLinux9](https://apps.microsoft.com/store/detail/almalinux-9/9P5RWLM70SN9));
  - [Athena-25.0.29](https://gitlab.cern.ch/atlas/athena/-/tags/release%2F25.0.29)
    set up (using
    [AtlasSetup](https://twiki.cern.ch/twiki/bin/view/AtlasComputing/AtlasSetupReference));
  - CUDA 12.4+ set up for the runtime environment such that CMake would also
    correctly find it.

## Exercises

The exercises are documented in individual Python notebooks. Please open these
to follow the individual exercises.
  - [Exercise 1](01_CUDA_LinearTransform.ipynb): Set up a simple CUDA algorithm,
    debug why it's not working, and fix its memory leaks.
  - [Exercise 2](02_CUDA_xAODCalib.ipynb): Work with a "more realistic" Athena
    algorithm that takes data from, and returns data to an xAOD container.
  - [Exercise 4](04_SYCL_LinearTransform.ipynb): Learn some basics about using
    SYCL to run simple kernels on a GPU.
