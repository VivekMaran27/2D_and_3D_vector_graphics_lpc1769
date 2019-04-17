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
all: lab2_3DGraphics_012556895.axf

# Tool invocations
lab2_3DGraphics_012556895.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\Users\vivek\Documents\MCUXpressoIDE_10.2.1_795\workspace\CMSIS_CORE_LPC17xx\Debug" -Xlinker -Map="lab2_3DGraphics_012556895.map" -Xlinker --gc-sections -Xlinker -print-memory-usage -mcpu=cortex-m3 -mthumb -T "lab2_3DGraphics_012556895_Debug.ld" -o "lab2_3DGraphics_012556895.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) lab2_3DGraphics_012556895.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "lab2_3DGraphics_012556895.axf"; # arm-none-eabi-objcopy -v -O binary "lab2_3DGraphics_012556895.axf" "lab2_3DGraphics_012556895.bin" ; # checksum -p LPC1769 -d "lab2_3DGraphics_012556895.bin";
	-@echo ' '

.PHONY: all clean dependents post-build

-include ../makefile.targets
