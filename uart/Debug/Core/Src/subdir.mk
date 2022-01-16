################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (9-2020-q2-update)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/hbridge.c \
../Core/Src/main.c \
../Core/Src/main_loop.c \
../Core/Src/main_preloop.c \
../Core/Src/mosfet.c \
../Core/Src/mux.c \
../Core/Src/servo.c \
../Core/Src/smbus.c \
../Core/Src/spectral.c \
../Core/Src/stm32g0xx_hal_msp.c \
../Core/Src/stm32g0xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/sysmem.c \
../Core/Src/system_stm32g0xx.c \
../Core/Src/thermistor.c \
../Core/Src/triad.c 

OBJS += \
./Core/Src/hbridge.o \
./Core/Src/main.o \
./Core/Src/main_loop.o \
./Core/Src/main_preloop.o \
./Core/Src/mosfet.o \
./Core/Src/mux.o \
./Core/Src/servo.o \
./Core/Src/smbus.o \
./Core/Src/spectral.o \
./Core/Src/stm32g0xx_hal_msp.o \
./Core/Src/stm32g0xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/sysmem.o \
./Core/Src/system_stm32g0xx.o \
./Core/Src/thermistor.o \
./Core/Src/triad.o 

C_DEPS += \
./Core/Src/hbridge.d \
./Core/Src/main.d \
./Core/Src/main_loop.d \
./Core/Src/main_preloop.d \
./Core/Src/mosfet.d \
./Core/Src/mux.d \
./Core/Src/servo.d \
./Core/Src/smbus.d \
./Core/Src/spectral.d \
./Core/Src/stm32g0xx_hal_msp.d \
./Core/Src/stm32g0xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/sysmem.d \
./Core/Src/system_stm32g0xx.d \
./Core/Src/thermistor.d \
./Core/Src/triad.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32G0B1xx -c -I../Core/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc -I../Drivers/STM32G0xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32G0xx/Include -I../Drivers/CMSIS/Include -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

