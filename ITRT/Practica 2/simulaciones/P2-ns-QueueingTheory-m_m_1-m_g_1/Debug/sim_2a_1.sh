#!/bin/bash

P='/home/labs/itrt/itrtx05/scripts2021/ITRT/P2-ns-QueueingTheory-m_m_1-m_g_1/Debug'

echo "Simulaciones para M/M/1"
for i in {1..100}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=10 --rep=$i >> $P/mm1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=0 --tmax=100 --rep=$i >> $P/mm1_100.txt
done

echo "Simulaciones para M/G/1"
for i in {1..100}
do
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=10 --rep=$i >> $P/mg1_10.txt
	$P/queue-mm1-mg1 --averaging=1 --fixedlength=1 --tmax=100 --rep=$i >> $P/mg1_100.txt
done
