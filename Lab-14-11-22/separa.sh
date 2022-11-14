#!/bin/bash

RESIDUE=${PATH}

#While RESIDUE is != 0
while [[ -n ${RESIDUE} ]]; do
    TO_PRINT=${RESIDUE%%:*}
    echo ${TO_PRINT}
    OLD_RESIDUE=${RESIDUE}
    RESIDUE=${RESIDUE#*:}

    #This prevents an infinite loop when only one path is present in RESIDUE.
    if [[ ${RESIDUE} == ${OLD_RESIDUE} ]]; then
        break;
    fi
done

