################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../JammerBox_Source/source/failures.c \
../JammerBox_Source/source/signal_saving.c \
../JammerBox_Source/source/synchronization.c \
../JammerBox_Source/source/system_configuration.c \
../JammerBox_Source/source/timer.c \
../JammerBox_Source/source/usart_soft.c 

OBJS += \
./JammerBox_Source/source/failures.o \
./JammerBox_Source/source/signal_saving.o \
./JammerBox_Source/source/synchronization.o \
./JammerBox_Source/source/system_configuration.o \
./JammerBox_Source/source/timer.o \
./JammerBox_Source/source/usart_soft.o 

C_DEPS += \
./JammerBox_Source/source/failures.d \
./JammerBox_Source/source/signal_saving.d \
./JammerBox_Source/source/synchronization.d \
./JammerBox_Source/source/system_configuration.d \
./JammerBox_Source/source/timer.d \
./JammerBox_Source/source/usart_soft.d 


# Each subdirectory must supply rules for building sources it contributes
JammerBox_Source/source/%.o JammerBox_Source/source/%.su: ../JammerBox_Source/source/%.c JammerBox_Source/source/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/hugom/Repos/PIR/MainSource/CompilationWithSTM32CubeIDE/JammerBox_Source/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-JammerBox_Source-2f-source

clean-JammerBox_Source-2f-source:
	-$(RM) ./JammerBox_Source/source/failures.d ./JammerBox_Source/source/failures.o ./JammerBox_Source/source/failures.su ./JammerBox_Source/source/signal_saving.d ./JammerBox_Source/source/signal_saving.o ./JammerBox_Source/source/signal_saving.su ./JammerBox_Source/source/synchronization.d ./JammerBox_Source/source/synchronization.o ./JammerBox_Source/source/synchronization.su ./JammerBox_Source/source/system_configuration.d ./JammerBox_Source/source/system_configuration.o ./JammerBox_Source/source/system_configuration.su ./JammerBox_Source/source/timer.d ./JammerBox_Source/source/timer.o ./JammerBox_Source/source/timer.su ./JammerBox_Source/source/usart_soft.d ./JammerBox_Source/source/usart_soft.o ./JammerBox_Source/source/usart_soft.su

.PHONY: clean-JammerBox_Source-2f-source

