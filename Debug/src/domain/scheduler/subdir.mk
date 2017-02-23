################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/domain/scheduler/scheduler.c 

OBJS += \
./src/domain/scheduler/scheduler.o 

C_DEPS += \
./src/domain/scheduler/scheduler.d 


# Each subdirectory must supply rules for building sources it contributes
src/domain/scheduler/%.o: ../src/domain/scheduler/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\extern_libs" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps\Micro1" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps\Micro2" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain\scheduler" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Display" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Display\Display_vga" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Buttons" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Keyboard" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Timer" -c -fmessage-length=0 -I../../zybo_vga_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


