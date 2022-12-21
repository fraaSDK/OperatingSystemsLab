#!/bin/bash

trap exit 0 SIGUSR2

echo Executing figlio.sh in bg.
./figlio.sh &
