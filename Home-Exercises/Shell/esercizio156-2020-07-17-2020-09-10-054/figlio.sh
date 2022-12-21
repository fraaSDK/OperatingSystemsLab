#!/bin/bash

echo figlio.sh is executing...
sleep 5

echo Sending SIGUSR2 signal to padre.sh
pkill -SIGUSR2 padre.sh
