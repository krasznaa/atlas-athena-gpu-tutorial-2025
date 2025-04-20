#!/bin/bash
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#
# Script executing the received command in the recommended environment of the
# tutorial. This is to help make the Jupyter notebooks a little simpler.
#

# Find the directory the script sits in.
SCRIPTDIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

# Set up the build environment. Done in such a way to avoid passing the command
# line arguments to ALRB.
env_setup() {
   source ${SCRIPTDIR}/build_env.sh
}
env_setup

# Run the command.
exec "$@" || exit 1
