################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/domain/analyse_position/analyse_position.c 

OBJS += \
./src/domain/analyse_position/analyse_position.o 

C_DEPS += \
./src/domain/analyse_position/analyse_position.d 


# Each subdirectory must supply rules for building sources it contributes
src/domain/analyse_position/%.o: ../src/domain/analyse_position/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM gcc compiler'
	arm-xilinx-eabi-gcc -Wall -O0 -g3 -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\store_SD" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps\visualize_data" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain\back_control" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\refresh_hw" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\libs\scheduler" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain\analyse_position" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain\back" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps\state_analyse" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps\store_data" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\libs\state_machine" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\extern_libs" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\apps" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\domain" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Display" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Display\Display_vga" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Buttons" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Leds" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Keyboard" -I"C:\METODOS_PROGRAMACION\workspaces\workspace_proyecto\proyecto1\src\hal\Timer" -c -fmessage-length=0 -MT"$@" -I../../zybo_base_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


