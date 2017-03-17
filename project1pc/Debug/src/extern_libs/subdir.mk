################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/extern_libs/platform.c 

OBJS += \
./src/extern_libs/platform.o 

C_DEPS += \
./src/extern_libs/platform.d 


# Each subdirectory must supply rules for building sources it contributes
src/extern_libs/%.o: ../src/extern_libs/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


