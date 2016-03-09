################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CHL_OLD_SRC/error/error.c 

OBJS += \
./CHL_OLD_SRC/error/error.o 

C_DEPS += \
./CHL_OLD_SRC/error/error.d 


# Each subdirectory must supply rules for building sources it contributes
CHL_OLD_SRC/error/%.o: ../CHL_OLD_SRC/error/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


