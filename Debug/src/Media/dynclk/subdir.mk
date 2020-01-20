################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Media/dynclk/dynclk.c 

OBJS += \
./src/Media/dynclk/dynclk.o 

C_DEPS += \
./src/Media/dynclk/dynclk.d 


# Each subdirectory must supply rules for building sources it contributes
src/Media/dynclk/%.o: ../src/Media/dynclk/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../SimpleFighter_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


