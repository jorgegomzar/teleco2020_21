#!/bin/bash

P='/home/ttr/Escritorio/ITRT/teleco2020_21/ITRT/Practica 2/simulaciones/P2-ns-QueueingTheory-m_m_1-m_g_1/Debug'

echo "Simulaciones para M/M/1"
for i in {1..500}
do
	./queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=10 --rep=$RANDOM >> ./mm1_10.txt
	./queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=100 --rep=$RANDOM >> ./mm1_100.txt
done

echo "Simulaciones para M/G/1"
for i in {1..500}
do
	./queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=10 --rep=$RANDOM >> ./mg1_10.txt
	./queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=100 --rep=$RANDOM >> ./mg1_100.txt
done
