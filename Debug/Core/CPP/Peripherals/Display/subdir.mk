################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/CPP/Peripherals/Display/Display.cpp 

OBJS += \
./Core/CPP/Peripherals/Display/Display.o 

CPP_DEPS += \
./Core/CPP/Peripherals/Display/Display.d 


# Each subdirectory must supply rules for building sources it contributes
Core/CPP/Peripherals/Display/%.o Core/CPP/Peripherals/Display/%.su Core/CPP/Peripherals/Display/%.cyclo: ../Core/CPP/Peripherals/Display/%.cpp Core/CPP/Peripherals/Display/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32/Bench_Test_CPP/Core/CPP" -I"D:/STM32/Bench_Test_CPP/Drivers/Motor control Display" -I"D:/STM32/Bench_Test_CPP/Drivers/MAX7219" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Watchdog" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Timer" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Motor" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Display" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/ADC" -I"D:/STM32/Bench_Test_CPP/Core/CPP/main" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/peripherals" -I"D:/STM32/Bench_Test_CPP/Core" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-CPP-2f-Peripherals-2f-Display

clean-Core-2f-CPP-2f-Peripherals-2f-Display:
	-$(RM) ./Core/CPP/Peripherals/Display/Display.cyclo ./Core/CPP/Peripherals/Display/Display.d ./Core/CPP/Peripherals/Display/Display.o ./Core/CPP/Peripherals/Display/Display.su

.PHONY: clean-Core-2f-CPP-2f-Peripherals-2f-Display

