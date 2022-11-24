#!/bin/bash

RIGA='1 * 2'

echo "${RIGA}" | while read A B C; do
	echo "$A"
	echo "$B"
	echo "$C"
done

# Itero fino a che la stringa ha qualcosa dentro
#while [[ -n "${RIGA}" ]]; do
	# copio prima parola, cioè quello che c'è fino al primo bianco
#	PAROLA="${RIGA%% *}"
	# Se a fine riga c'è spazio bianco allora non sono riusciuto ad
	# estrarre la parola, e ho preso tutta la riga.
	# Se ho preso tutta la riga vuol dire che sono alla fine.
#	if [[ "${PAROLA}" == "${RIGA}" ]]; then
#		RIGA=
#	else
		# rimuovo la prima parola e il successivo bianco
#		RIGA="${RIGA#* }"
#	fi
#	echo "${PAROLA}"
#done
