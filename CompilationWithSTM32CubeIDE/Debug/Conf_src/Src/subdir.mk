################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/failures.c \
C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/synchronization.c \
C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/system_configuration.c \
C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/timer.c \
C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/usart_soft.c 

OBJS += \
./Conf_src/Src/failures.o \
./Conf_src/Src/synchronization.o \
./Conf_src/Src/system_configuration.o \
./Conf_src/Src/timer.o \
./Conf_src/Src/usart_soft.o 

C_DEPS += \
./Conf_src/Src/failures.d \
./Conf_src/Src/synchronization.d \
./Conf_src/Src/system_configuration.d \
./Conf_src/Src/timer.d \
./Conf_src/Src/usart_soft.d 


# Each subdirectory must supply rules for building sources it contributes
Conf_src/Src/failures.o: C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/failures.c Conf_src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HMathieu/Repos/PIR/Nouveau Pir/firmware/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Conf_src/Src/synchronization.o: C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/synchronization.c Conf_src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HMathieu/Repos/PIR/Nouveau Pir/firmware/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Conf_src/Src/system_configuration.o: C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/system_configuration.c Conf_src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HMathieu/Repos/PIR/Nouveau Pir/firmware/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Conf_src/Src/timer.o: C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/timer.c Conf_src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HMathieu/Repos/PIR/Nouveau Pir/firmware/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Conf_src/Src/usart_soft.o: C:/Users/HMathieu/Repos/PIR/Nouveau\ Pir/firmware/source/usart_soft.c Conf_src/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103xB -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/HMathieu/Repos/PIR/Nouveau Pir/firmware/header" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Conf_src-2f-Src

clean-Conf_src-2f-Src:
	-$(RM) ./Conf_src/Src/failures.d ./Conf_src/Src/failures.o ./Conf_src/Src/failures.su ./Conf_src/Src/synchronization.d ./Conf_src/Src/synchronization.o ./Conf_src/Src/synchronization.su ./Conf_src/Src/system_configuration.d ./Conf_src/Src/system_configuration.o ./Conf_src/Src/system_configuration.su ./Conf_src/Src/timer.d ./Conf_src/Src/timer.o ./Conf_src/Src/timer.su ./Conf_src/Src/usart_soft.d ./Conf_src/Src/usart_soft.o ./Conf_src/Src/usart_soft.su

.PHONY: clean-Conf_src-2f-Src

