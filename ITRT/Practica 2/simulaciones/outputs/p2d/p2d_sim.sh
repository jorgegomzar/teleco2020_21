#!/bin/bash
BLUE=$(tput setaf 4)
YELLOW=$(tput setaf 3)
NORMAL=$(tput sgr0)

echo "" > 1000_mm1.csv
echo "" > 1000_mg1.csv


printf "${BLUE}1000 SIMULACIONES - M/M/1${NORMAL}\n"
for i in {1..1000}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
	../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 1000_mm1.csv
done

printf "${BLUE}1000 SIMULACIONES - M/G/1${NORMAL}\n"
for i in {1..1000}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 1000_mg1.csv
done