#!/bin/bash
# Reset ficheros
echo "" > ./mm1_10.csv
echo "" > ./mm1_10.csv
echo "" > ./mg1_100.csv
echo "" > ./mg1_100.csv

YELLOW=$(tput setaf 3)
BLUE=$(tput setaf 4)
NORMAL=$(tput sgr0)

for i in {1..500}
do
	# M/M/1
	printf "${YELLOW} - Iteración ${i} - ${NORMAL}\n"
	../../queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=10 --rep=$RANDOM >> ./mm1_10.csv
	../../queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=100 --rep=$RANDOM >> ./mm1_100.csv

	# M/G/1
	../../queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=10 --rep=$RANDOM >> ./mg1_10.csv
	../../queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=100 --rep=$RANDOM >> ./mg1_100.csv
done


