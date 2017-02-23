################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/libs/state_machine/subdir.mk
-include src/libs/scheduler/subdir.mk
-include src/hal/store_SD/subdir.mk
-include src/hal/refresh_hw/subdir.mk
-include src/hal/Timer/subdir.mk
-include src/hal/Leds/subdir.mk
-include src/hal/Keyboard/subdir.mk
-include src/hal/Display/Display_vga/subdir.mk
-include src/hal/Display/subdir.mk
-include src/hal/Buttons/subdir.mk
-include src/extern_libs/subdir.mk
-include src/domain/back_control/subdir.mk
-include src/domain/back/subdir.mk
-include src/domain/analyse_position/subdir.mk
-include src/domain/subdir.mk
-include src/apps/visualize_data/subdir.mk
-include src/apps/store_data/subdir.mk
-include src/apps/state_analyse/subdir.mk
-include src/apps/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
ELFSIZE += \
proyecto1.elf.size \


# All Target
all: proyecto1.elf secondary-outputs

# Tool invocations
proyecto1.elf: $(OBJS) ../src/lscript.ld $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: ARM gcc linker'
	arm-xilinx-eabi-gcc -Wl,-T -Wl,../src/lscript.ld -L../../zybo_base_bsp/ps7_cortexa9_0/lib -o "proyecto1.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

proyecto1.elf.size: proyecto1.elf
	@echo 'Invoking: ARM Print Size'
	arm-xilinx-eabi-size proyecto1.elf  |tee "proyecto1.elf.size"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(S_UPPER_DEPS)$(C_DEPS)$(ELFSIZE) proyecto1.elf
	-@echo ' '

secondary-outputs: $(ELFSIZE)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
