################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CHL_OLD_SRC/io/io.c 

OBJS += \
./CHL_OLD_SRC/io/io.o 

C_DEPS += \
./CHL_OLD_SRC/io/io.d 


# Each subdirectory must supply rules for building sources it contributes
CHL_OLD_SRC/io/%.o: ../CHL_OLD_SRC/io/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


