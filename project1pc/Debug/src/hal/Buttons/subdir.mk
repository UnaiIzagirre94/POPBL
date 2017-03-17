################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/hal/Buttons/Buttons_services.c 

OBJS += \
./src/hal/Buttons/Buttons_services.o 

C_DEPS += \
./src/hal/Buttons/Buttons_services.d 


# Each subdirectory must supply rules for building sources it contributes
src/hal/Buttons/%.o: ../src/hal/Buttons/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


