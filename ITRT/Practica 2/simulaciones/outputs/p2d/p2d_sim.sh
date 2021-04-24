#!/bin/bash

echo "" > 10_mm1.csv
echo "" > 10_mg1.csv
echo "" > 50_mm1.csv
echo "" > 50_mg1.csv
echo "" > 100_mm1.csv
echo "" > 100_mg1.csv
echo "" > 200_mm1.csv
echo "" > 200_mg1.csv

for i in {1..10}
do
	../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 10_mm1.csv
	../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 10_mg1.csv
done

for i in {1..50}
do
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 50_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 50_mg1.csv
done

for i in {1..100}
do
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 100_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 100_mg1.csv
done

for i in {1..200}
do
        ../queue-mm1-mg1 --averaging=0 --tmax=10000 --rep=$RANDOM >> 200_mm1.csv
        ../queue-mm1-mg1 --averaging=0 --fixedlength=1 --tmax=10000 --rep=$RANDOM >> 200_mg1.csv
done


