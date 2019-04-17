################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/coord.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/lcd_utils.c \
../src/main.c \
../src/queue.c \
../src/shrinking_squares.c \
../src/ssp.c \
../src/trees.c 

OBJS += \
./src/coord.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/lcd_utils.o \
./src/main.o \
./src/queue.o \
./src/shrinking_squares.o \
./src/ssp.o \
./src/trees.o 

C_DEPS += \
./src/coord.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/lcd_utils.d \
./src/main.d \
./src/queue.d \
./src/shrinking_squares.d \
./src/ssp.d \
./src/trees.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\vivek\Documents\MCUXpressoIDE_10.2.1_795\workspace\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


