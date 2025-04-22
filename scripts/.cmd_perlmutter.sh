#!/bin/bash
#
# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration
#

# Find the directory the script sits in.
SCRIPTDIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

# Set up the environment.
env_perlmutter() {
   source "${SCRIPTDIR}/.env_perlmutter.sh"
}
env_perlmutter

# Run the received command.
exec "$@" || exit 1
