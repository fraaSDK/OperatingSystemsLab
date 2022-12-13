#!/bin/bash

#Iterating over all directory's files, $? checks the exit status of the ls command.
for file in `ls`; do echo file is $file; ls -ld $file; if (($? != 0)); then echo ls produce errore; fi; done
