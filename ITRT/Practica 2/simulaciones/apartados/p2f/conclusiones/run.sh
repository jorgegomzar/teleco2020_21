#!/bin/bash

SIM=./queue-datanetwork

rm -f *trace

# M/M/1
# Los tiempos entre llegadas tienen una distrib exponencial
# Los tiempos entre salidas tienen un distrib exponencial -> tam paquetes distrib exp a R cte
# Cola lo suficientemente grande (senderIPBufferSize)
$SIM --fixedlength=0 --meanPacketSize=200 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=1000

mv P2-ns-QueueingTheory-arrivals.trace mm1_arrivals.trace
mv receiver.enqueue.trace mm1_receiver.enqueue.trace
mv sender.dequeue.trace mm1_sender.dequeue.trace
mv sender.enqueue.trace mm1_sender.enqueue.trace
mv sender.queuedropped.trace mm1_sender.queuedropped.trace

# M/D/1
# Los tiempos entre llegadas tienen una distrib exponencial
# Los tiempos entre salidas tienen una distrib uniforme -> tam paquetes cte a R cte
# Cola lo suficientemente grande (senderIPBufferSize)
$SIM --fixedlength=1 --meanPacketSize=200 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=1000

mv P2-ns-QueueingTheory-arrivals.trace md1_arrivals.trace
mv receiver.enqueue.trace md1_receiver.enqueue.trace
mv sender.dequeue.trace md1_sender.dequeue.trace
mv sender.enqueue.trace md1_sender.enqueue.trace
mv sender.queuedropped.trace md1_sender.queuedropped.trace

# M/M/1/k
# Los tiempos entre llegadas tienen una distrib exponencial
# Los tiempos entre salidas tienen un distrib exponencial -> tam paquetes distrib exp a R cte
# Cola finita (senderIPBufferSize)
$SIM --fixedlength=0 --meanPacketSize=200 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=3

mv P2-ns-QueueingTheory-arrivals.trace mm1k_arrivals.trace
mv receiver.enqueue.trace mm1k_receiver.enqueue.trace
mv sender.dequeue.trace mm1k_sender.dequeue.trace
mv sender.enqueue.trace mm1k_sender.enqueue.trace
mv sender.queuedropped.trace mm1k_sender.queuedropped.trace

# M/D/1/k
# Los tiempos entre llegadas tienen una distrib exponencial
# Los tiempos entre salidas tienen un distrib uniforme -> tam paquetes uniforme a R cte
# Cola finita (senderIPBufferSize)
$SIM --fixedlength=1 --meanPacketSize=200 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=3

mv P2-ns-QueueingTheory-arrivals.trace md1k_arrivals.trace
mv receiver.enqueue.trace md1k_receiver.enqueue.trace
mv sender.dequeue.trace md1k_sender.dequeue.trace
mv sender.enqueue.trace md1k_sender.enqueue.trace
mv sender.queuedropped.trace md1k_sender.queuedropped.trace

# G/M/1
# Los tiempos entre llegadas no tienen una distrib exponencial???? -> caso de fragmentacion?
# Los tiempos entre salidas tienen un distrib exponencial -> tam paquetes distrib exp a R cte
# Cola lo suficientemente grande (senderIPBufferSize)
$SIM --fixedlength=0 --meanPacketSize=1500 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=1000

mv P2-ns-QueueingTheory-arrivals.trace gm1_arrivals.trace
mv receiver.enqueue.trace gm1_receiver.enqueue.trace
mv sender.dequeue.trace gm1_sender.dequeue.trace
mv sender.enqueue.trace gm1_sender.enqueue.trace
mv sender.queuedropped.trace gm1_sender.queuedropped.trace

# G/G/1
# Los tiempos entre llegadas no tienen una distrib exponencial???? -> caso de fragmentacion?
# Los tiempos entre salidas no tienen un distrib exponencial -> tam paquetes cte exp a R cte
# Cola lo suficientemente grande (senderIPBufferSize)
$SIM --fixedlength=1 --meanPacketSize=1500 --tmax=10000 --tracing=1 --averaging=0 --rep=$RANDOM --senderIPBufferSize=1000

mv P2-ns-QueueingTheory-arrivals.trace gg1_arrivals.trace
mv receiver.enqueue.trace gg1_receiver.enqueue.trace
mv sender.dequeue.trace gg1_sender.dequeue.trace
mv sender.enqueue.trace gg1_sender.enqueue.trace
mv sender.queuedropped.trace gg1_sender.queuedropped.trace
