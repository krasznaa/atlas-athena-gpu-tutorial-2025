#!/bin/bash
setupATLAS () 
{ 
    if [ -d $ATLAS_LOCAL_ROOT_BASE ]; then
        source $ATLAS_LOCAL_ROOT_BASE/user/atlasLocalSetup.sh;
        return $?;
    else
        \echo "Error: atlas repo ($ATLAS_LOCAL_ROOT_BASE) is unavailable";
        return 64;
    fi
}
echo CUDA AT $CUDA_HOME
APPTAINERENV_CUDA_HOME="$CUDA_HOME" setupATLAS -c el9 -e "--nv" -e "-B $CUDA_HOME"

