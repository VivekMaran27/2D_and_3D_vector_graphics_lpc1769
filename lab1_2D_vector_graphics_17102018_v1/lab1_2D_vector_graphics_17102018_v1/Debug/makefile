################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
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
all: lab1_2D_vector_graphics_17102018_v1.axf

# Tool invocations
lab1_2D_vector_graphics_17102018_v1.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\vivek\Documents\MCUXpressoIDE_10.2.1_795\workspace\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="lab1_2D_vector_graphics_17102018_v1.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "lab1_2D_vector_graphics_17102018_v1_Debug.ld" -o "lab1_2D_vector_graphics_17102018_v1.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) lab1_2D_vector_graphics_17102018_v1.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lab1_2D_vector_graphics_17102018_v1.axf"; # arm-none-eabi-objcopy -v -O binary "lab1_2D_vector_graphics_17102018_v1.axf" "lab1_2D_vector_graphics_17102018_v1.bin" ; # checksum -p LPC1769 -d "lab1_2D_vector_graphics_17102018_v1.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
