#!/bin/bash

#Attenzione, se non esiste il file la command substitution può fallire
#for char in {c..g} ; do
#    for name in `find /usr/include/?$char* -maxdepth 0` ; do
#        if [[ ${#name} -lt 18 || ${#name} -gt 23 ]] ; then
#            echo $name
#        fi
#    done
#done

for name in /usr/include/?{c..g}* ; do
    if [[ ${#name} -lt 18 || ${#name} -gt 23 ]] ; then
        echo $name
    fi
done
