################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../Sender.cc \
../diff-serv-aqm.cc \
../diff-serv-flow.cc \
../diff-serv-meter.cc \
../diff-serv-queue.cc \
../diff-serv-sla.cc \
../diffservtest.cc \
../srtcm.cc \
../stat-collector.cc \
../token-bucket.cc \
../trtcm.cc \
../wred.cc 

OBJS += \
./Sender.o \
./diff-serv-aqm.o \
./diff-serv-flow.o \
./diff-serv-meter.o \
./diff-serv-queue.o \
./diff-serv-sla.o \
./diffservtest.o \
./srtcm.o \
./stat-collector.o \
./token-bucket.o \
./trtcm.o \
./wred.o 

CC_DEPS += \
./Sender.d \
./diff-serv-aqm.d \
./diff-serv-flow.d \
./diff-serv-meter.d \
./diff-serv-queue.d \
./diff-serv-sla.d \
./diffservtest.d \
./srtcm.d \
./stat-collector.d \
./token-bucket.d \
./trtcm.d \
./wred.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DNS3_LOG_ENABLE -I/usr/local/ns-allinone-3.16/ns-3.16/build -I. -I/usr/local/ns-allinone-3.16/ns-3.16/src/internet/model -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


