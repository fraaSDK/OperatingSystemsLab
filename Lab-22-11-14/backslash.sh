#!/bin/bash

# Substitution of strings ${VAR//pattern/string}
while read LINE; do
    LINE="${LINE//'*'/'\*'}"
    LINE="${LINE//'?'/'\?'}"
    LINE="${LINE//'['/'\['}"
    LINE="${LINE//']'/'\]'}"
    echo "${LINE}"
done

