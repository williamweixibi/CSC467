################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
O_SRCS += \
../compiler467.o \
../globalvars.o \
../parser.o \
../scanner.o 

C_SRCS += \
../compiler467.c \
../file.c \
../globalvars.c \
../parser.c 

OBJS += \
./compiler467.o \
./file.o \
./globalvars.o \
./parser.o 

C_DEPS += \
./compiler467.d \
./file.d \
./globalvars.d \
./parser.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


