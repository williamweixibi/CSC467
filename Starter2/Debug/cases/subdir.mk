################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cases/test1.c \
../cases/test2.c \
../cases/test3.c \
../cases/test4.c \
../cases/test5.c \
../cases/test6.c \
../cases/test7.c 

OBJS += \
./cases/test1.o \
./cases/test2.o \
./cases/test3.o \
./cases/test4.o \
./cases/test5.o \
./cases/test6.o \
./cases/test7.o 

C_DEPS += \
./cases/test1.d \
./cases/test2.d \
./cases/test3.d \
./cases/test4.d \
./cases/test5.d \
./cases/test6.d \
./cases/test7.d 


# Each subdirectory must supply rules for building sources it contributes
cases/%.o: ../cases/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


