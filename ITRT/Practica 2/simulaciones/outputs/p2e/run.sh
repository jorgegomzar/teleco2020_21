#!/bin/bash

printf "Simulacion sin fragmentacion, L=1472 B"
./queue-datanetwork --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=1472 --fixedlength=1 --tracing=1


printf "Simulacion con fragmentacion, L=1473 B"
./queue-datanetwork --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=1473 --fixedlength=1 --tracing=1
