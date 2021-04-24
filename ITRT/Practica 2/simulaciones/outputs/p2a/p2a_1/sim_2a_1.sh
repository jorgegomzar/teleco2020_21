#!/bin/bash

echo "" > ./mm1_10.txt
echo "" > ./mm1_10.txt
echo "" > ./mg1_100.txt
echo "" > ./mg1_100.txt

P='../..'
YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
NORMAL=$(tput sgr0)

printf "${BLUE}Simulaciones M/M/1${NORMAL}\n"
for i in {1..500}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=10 --rep=$RANDOM >> ./mm1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=100 --rep=$RANDOM >> ./mm1_100.txt
done

printf "${BLUE}Simulaciones M/G/1${NORMAL}\n"
for i in {1..500}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=10 --rep=$RANDOM >> ./mg1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=100 --rep=$RANDOM >> ./mg1_100.txt
done
