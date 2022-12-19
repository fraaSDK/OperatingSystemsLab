#!/bin/bash

if (( $# != 2 )) ; then 
	echo "errore: servono 2 argomenti: larghezza_minima  altezza_massima"
	exit 1
fi

LARGMIN=$1
ALTMAX=$2

# ORA nelle due variabili ci sono i parametri
# passati a riga di comando.
# Da qui in poi aggiungete quello che serve.
# Leggete il contenuto del file ./divani.txt
# ed usatelo opportunamente.

while read NAME WIDTH HEIGHT OTHER; do
	if (( ${WIDTH} >= ${LARGMIN} && ${HEIGHT} <= ${ALTMAX} )); then
		echo "${NAME} ${WIDTH} ${HEIGHT} ${OTHER}"
	fi
done < ./divani.txt
