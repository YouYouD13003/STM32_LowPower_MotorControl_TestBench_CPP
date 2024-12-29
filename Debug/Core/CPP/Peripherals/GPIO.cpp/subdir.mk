################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../Core/CPP/Peripherals/GPIO.cpp/GPIO.cpp 

OBJS += \
./Core/CPP/Peripherals/GPIO.cpp/GPIO.o 

CPP_DEPS += \
./Core/CPP/Peripherals/GPIO.cpp/GPIO.d 


# Each subdirectory must supply rules for building sources it contributes
Core/CPP/Peripherals/GPIO.cpp/%.o Core/CPP/Peripherals/GPIO.cpp/%.su Core/CPP/Peripherals/GPIO.cpp/%.cyclo: ../Core/CPP/Peripherals/GPIO.cpp/%.cpp Core/CPP/Peripherals/GPIO.cpp/subdir.mk
	arm-none-eabi-g++ "$<" -mcpu=cortex-m3 -std=gnu++14 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32L152xE -c -I../Core/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc -I../Drivers/STM32L1xx_HAL_Driver/Inc/Legacy -I../Drivers/CMSIS/Device/ST/STM32L1xx/Include -I../Drivers/CMSIS/Include -I"D:/STM32/Bench_Test_CPP/Core/CPP" -I"D:/STM32/Bench_Test_CPP/Drivers/Motor control Display" -I"D:/STM32/Bench_Test_CPP/Drivers/MAX7219" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Watchdog" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Timer" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Motor" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/Display" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/ADC" -I"D:/STM32/Bench_Test_CPP/Core/CPP/main" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/peripherals" -I"D:/STM32/Bench_Test_CPP/Core" -I"D:/STM32/Bench_Test_CPP/Core/CPP/Peripherals/GPIO.cpp" -O0 -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -fno-use-cxa-atexit -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-CPP-2f-Peripherals-2f-GPIO-2e-cpp

clean-Core-2f-CPP-2f-Peripherals-2f-GPIO-2e-cpp:
	-$(RM) ./Core/CPP/Peripherals/GPIO.cpp/GPIO.cyclo ./Core/CPP/Peripherals/GPIO.cpp/GPIO.d ./Core/CPP/Peripherals/GPIO.cpp/GPIO.o ./Core/CPP/Peripherals/GPIO.cpp/GPIO.su

.PHONY: clean-Core-2f-CPP-2f-Peripherals-2f-GPIO-2e-cpp

