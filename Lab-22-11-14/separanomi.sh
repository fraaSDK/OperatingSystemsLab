#!/bin/bash

RESIDUE=${PATH}

#While RESIDUE is != 0
while [[ -n ${RESIDUE} ]]; do
    VALUE=${RESIDUE%%:*}

    # Used to ignore windows wsl folders.
    if [[ $VALUE == *"mnt"* ]]; then
        OLD_RESIDUE=${RESIDUE}
        RESIDUE=${RESIDUE#*;}
        if [[ ${RESIDUE} == ${OLD_RESIDUE} ]]; then
            break;
        fi
        continue
    fi

    TO_PRINT=${VALUE##*/}
    echo ${TO_PRINT}
    OLD_RESIDUE=${RESIDUE}
    RESIDUE=${RESIDUE#*:}

    #This prevents an infinite loop when only one path is present in RESIDUE.
    if [[ ${RESIDUE} == ${OLD_RESIDUE} ]]; then
        break;
    fi
done

