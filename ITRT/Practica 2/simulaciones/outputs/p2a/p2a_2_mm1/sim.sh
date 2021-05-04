#!/bin/bash


for i in {1..2000}
do
	t=$((i * 10))
	printf "Iteracion ${i} - ${t}\n"

	../../queue-mm1-mg1 --tmax=$t --fixedlength=0 --averaging=1 >> mm1_q.csv
	../../queue-mm1-mg1 --tmax=$t --fixedlength=1 --averaging=1 >> mg1_q.csv
done
