################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../queue-datanetwork.cc 

CC_DEPS += \
./queue-datanetwork.d 

OBJS += \
./queue-datanetwork.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -DNS3_LOG_ENABLE -I/usr/local/ns-allinone-3.16/ns-3.16/build -I. -I/usr/local/ns-allinone-3.16/ns-3.16/src/internet/model -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


