#!/bin/bash

while read VERDETTO_ID VERDETTO; do
    while read DENUNCIA_ID PROCESSO_ID; do

        if [[ $VERDETTO_ID == $PROCESSO_ID ]]; then
            while read NOME COGNOME denuncia_id DENUNCIA; do
                if [[ $DENUNCIA_ID == $denuncia_id ]]; then
                    echo "${NOME} ${COGNOME} | ${DENUNCIA} | ${VERDETTO}"
                fi
            done < ./denunce.txt
        fi

    done < ./processi.txt
done < ./verdetti.txt
