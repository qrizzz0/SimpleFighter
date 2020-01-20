################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/Media/Graphics.c \
../src/Media/SDCard.c 

OBJS += \
./src/Media/Graphics.o \
./src/Media/SDCard.o 

C_DEPS += \
./src/Media/Graphics.d \
./src/Media/SDCard.d 


# Each subdirectory must supply rules for building sources it contributes
src/Media/%.o: ../src/Media/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../SimpleFighter_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


