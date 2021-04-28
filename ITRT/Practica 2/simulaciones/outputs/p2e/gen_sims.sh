#!/bin/bash
BLUE=$(tput setaf 4)
YELLOW=$(tput setaf 3)
NORMAL=$(tput sgr0)

echo "" > mm1_def.csv
echo "" > mg1_def.csv
echo "" > mm1_frag.csv
echo "" > mg1_frag.csv

printf "${BLUE}Generacion de simulaciones SIN fragmentacion:${NORMAL}\n"
for i in {1..100}:
do
	printf "${YELLOW} - iteracion $i ${NORMAL}\n"
	# M/M/1, meanPacketSize=200
	../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=200 --fixedlength=0 >> mm1_def.csv
	# M/G/1, meanPacketSize=200
	../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=200 --fixedlength=1 >> mg1_def.csv
done

printf "${BLUE}Generacion de simulaciones CON fragmentacion:${NORMAL}\n"
for i in {1..100}:
do
        printf "${YELLOW} - iteracion $i ${NORMAL}\n"
        # M/M/1, meanPacketSize=1500
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=1500 --fixedlength=0 >> mm1_frag.csv
	# M/G/1, meanPacketSize=1500
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM --meanPacketSize=1500 --fixedlength=1 >> mg1_frag.csv
done
