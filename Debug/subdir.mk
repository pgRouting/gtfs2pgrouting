################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../data_loader.c \
../gtfs2pgrouting.c \
../sql_utils.c \
../verbosity.c 

OBJS += \
./data_loader.o \
./gtfs2pgrouting.o \
./sql_utils.o \
./verbosity.o 

C_DEPS += \
./data_loader.d \
./gtfs2pgrouting.d \
./sql_utils.d \
./verbosity.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I/usr/include/postgresql -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


