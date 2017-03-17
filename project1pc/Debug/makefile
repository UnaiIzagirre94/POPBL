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
-include src/hal/keyboard/subdir.mk
-include src/domain/back_control/subdir.mk
-include src/domain/back/subdir.mk
-include src/domain/analyse_position/subdir.mk
-include src/apps/visualize_data/subdir.mk
-include src/apps/store_data/subdir.mk
-include src/apps/state_analyse/subdir.mk
-include src/apps/subdir.mk
-include .metadata/.plugins/org.eclipse.cdt.make.core/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: project1pc

# Tool invocations
project1pc: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C Linker'
	gcc  -o "project1pc" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) project1pc
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
