/*
 * main.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub abbes
 */

#ifndef CPP_MAIN_HPP_
#define CPP_MAIN_HPP_

#include "stm32l1xx_hal.h"
#include <stdio.h>

// Include the necessary peripheral headers
#include "Peripherals/Motor/Motor.hpp"
#include "Peripherals/Display/Display.hpp"
#include "Peripherals/ADC/ADC.hpp"
#include "Peripherals/Timer/Timer.hpp"
#include "Peripherals/Watchdog/Watchdog.hpp"

#ifdef __cplusplus
extern "C" {
#endif

// Prototype for _write and HAL callbacks
int _write(int file, char *ptr, int len);
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void main_cpp(void);

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

// TestBench class definition
class TestBench {
public:
	// Constructor: Initialize with references to peripherals
	TestBench(Motor &motor, Display &display, Adc &adc, Timer &basicTimer,
			Timer &PWM_Timer, Watchdog &watchdog);

	// Method to initialize all peripherals
	void initialize_peripherals();

	// Method to run the test bench operations
	void run();

	// Method to manage sleep mode
	void sleep();

private:
	Motor &motor;
	Display &display;
	Adc &adc;
	Timer &basicTimer;
	Timer &PWM_Timer;
	Watchdog &watchdog;
};

#endif /* __cplusplus */

#endif /* CPP_MAIN_HPP_ */
