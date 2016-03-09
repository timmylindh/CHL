################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CHL_OLD_SRC/core/cgi.c \
../CHL_OLD_SRC/core/vas.c \
../CHL_OLD_SRC/core/view.c 

OBJS += \
./CHL_OLD_SRC/core/cgi.o \
./CHL_OLD_SRC/core/vas.o \
./CHL_OLD_SRC/core/view.o 

C_DEPS += \
./CHL_OLD_SRC/core/cgi.d \
./CHL_OLD_SRC/core/vas.d \
./CHL_OLD_SRC/core/view.d 


# Each subdirectory must supply rules for building sources it contributes
CHL_OLD_SRC/core/%.o: ../CHL_OLD_SRC/core/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


