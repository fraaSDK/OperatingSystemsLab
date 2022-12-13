#!/bin/bash

while read NAME SURNAME ID GRADE; do
    FOUND_ID=`grep ${ID} RisultatiProvaPratica1.txt`
    if [[ -z ${FOUND_ID} ]]; then
        if (( ${GRADE} < 18 )); then
            echo "${ID} ${NAME} ${SURNAME} ${GRADE}"
        fi
    fi
done < RisultatiProvaPratica2.txt | sort -k 3
