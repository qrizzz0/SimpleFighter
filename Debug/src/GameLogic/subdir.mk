################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/GameLogic/GameLoop.c \
../src/GameLogic/animation.c \
../src/GameLogic/controls.c \
../src/GameLogic/map.c 

OBJS += \
./src/GameLogic/GameLoop.o \
./src/GameLogic/animation.o \
./src/GameLogic/controls.o \
./src/GameLogic/map.o 

C_DEPS += \
./src/GameLogic/GameLoop.d \
./src/GameLogic/animation.d \
./src/GameLogic/controls.d \
./src/GameLogic/map.d 


# Each subdirectory must supply rules for building sources it contributes
src/GameLogic/%.o: ../src/GameLogic/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: ARM v7 gcc compiler'
	arm-none-eabi-gcc -Wall -O0 -g3 -c -fmessage-length=0 -MT"$@" -mcpu=cortex-a9 -mfpu=vfpv3 -mfloat-abi=hard -I../../SimpleFighter_bsp/ps7_cortexa9_0/include -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


