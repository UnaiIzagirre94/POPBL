################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/domain/back_control/back_control.c 

OBJS += \
./src/domain/back_control/back_control.o 

C_DEPS += \
./src/domain/back_control/back_control.d 


# Each subdirectory must supply rules for building sources it contributes
src/domain/back_control/%.o: ../src/domain/back_control/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/domain/analyse_position" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/extern_libs" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/domain/back" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/domain/back_control" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/apps" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/apps/store_data" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/apps/state_analyse" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/apps/visualize_data" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/hal/refresh_hw" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/libs/state_machine" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/hal/keyboard" -I"/home/unai/workspace/MANTENIMIENTO/project1pc/src/hal/store_SD" -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


