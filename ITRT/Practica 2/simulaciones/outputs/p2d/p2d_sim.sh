#!/bin/bash
BLUE=$(tput setaf 4)
YELLOW=$(tput setaf 3)
NORMAL=$(tput sgr0)

echo "" > 10_mm1.csv
echo "" > 10_mg1.csv
echo "" > 50_mm1.csv
echo "" > 50_mg1.csv
echo "" > 100_mm1.csv
echo "" > 100_mg1.csv
echo "" > 200_mm1.csv
echo "" > 200_mg1.csv


printf "${BLUE}10 SIMULACIONES - M/M/1 y M/G/1${NORMAL}\n"
for i in {1..10}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
	../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 10_mm1.csv
	../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 10_mg1.csv
done

printf "${BLUE}50 SIMULACIONES - M/M/1 y M/G/1${NORMAL}\n"
for i in {1..50}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 50_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 50_mg1.csv
done

printf "${BLUE}100 SIMULACIONES - M/M/1 y M/G/1${NORMAL}\n"
for i in {1..100}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 100_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 100_mg1.csv
done

printf "${BLUE}200 SIMULACIONES - M/M/1 y M/G/1${NORMAL}\n"
for i in {1..200}
do
	printf "${YELLOW} - iteración $i ${NORMAL}\n"
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 200_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 200_mg1.csv
done


