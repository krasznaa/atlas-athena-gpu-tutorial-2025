# Copyright (C) 2002-2025 CERN for the benefit of the ATLAS collaboration

# Find the directory the script sits in.
SCRIPTDIR=$(cd $(dirname ${BASH_SOURCE[0]}) && pwd)

# Set up the build environment. Done in such a way to avoid passing the command
# line arguments to ALRB.
env_setup() {
   source ${SCRIPTDIR}/.env_swan_oneapi.sh
}
env_setup
