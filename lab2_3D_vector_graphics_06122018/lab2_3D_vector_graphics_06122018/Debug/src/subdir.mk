################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/2d_graphics.c \
../src/3d_conv.c \
../src/3d_graphics.c \
../src/coord.c \
../src/cr_startup_lpc175x_6x.c \
../src/crp.c \
../src/lcd_utils.c \
../src/main.c \
../src/ssp.c 

OBJS += \
./src/2d_graphics.o \
./src/3d_conv.o \
./src/3d_graphics.o \
./src/coord.o \
./src/cr_startup_lpc175x_6x.o \
./src/crp.o \
./src/lcd_utils.o \
./src/main.o \
./src/ssp.o 

C_DEPS += \
./src/2d_graphics.d \
./src/3d_conv.d \
./src/3d_graphics.d \
./src/coord.d \
./src/cr_startup_lpc175x_6x.d \
./src/crp.d \
./src/lcd_utils.d \
./src/main.d \
./src/ssp.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__CODE_RED -DCORE_M3 -D__USE_CMSIS=CMSIS_CORE_LPC17xx -D__LPC17XX__ -D__REDLIB__ -I"C:\Users\vivek\Documents\MCUXpressoIDE_10.2.1_795\workspace\CMSIS_CORE_LPC17xx\inc" -O0 -fno-common -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m3 -mthumb -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


