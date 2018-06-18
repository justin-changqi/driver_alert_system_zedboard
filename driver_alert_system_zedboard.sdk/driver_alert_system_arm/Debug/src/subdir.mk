################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
LD_SRCS += \
../src/lscript.ld 

C_SRCS += \
../src/can.c \
../src/common.c \
../src/gpio.c \
../src/i2c.c \
../src/main.c \
../src/platform.c \
../src/timer.c 

OBJS += \
./src/can.o \
./src/common.o \
./src/gpio.o \
./src/i2c.o \
./src/main.o \
./src/platform.o \
./src/timer.o 

C_DEPS += \
./src/can.d \
./src/common.d \
./src/gpio.d \
./src/i2c.d \
./src/main.d \
./src/platform.d \
./src/timer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../driver_alert_system_arm_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


