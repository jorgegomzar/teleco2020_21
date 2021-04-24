#!/bin/bash

P='../..'

echo "Simulaciones para M/M/1"
for i in {1..500}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=10 --rep=$RANDOM >> ./mm1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=100 --rep=$RANDOM >> ./mm1_100.txt
done

echo "Simulaciones para M/G/1"
for i in {1..500}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=10 --rep=$RANDOM >> ./mg1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=100 --rep=$RANDOM >> ./mg1_100.txt
done
