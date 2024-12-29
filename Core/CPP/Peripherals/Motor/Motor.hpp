/*
 * Motor.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef CPP_PERIPHERALS_MOTOR_MOTOR_HPP_
#define CPP_PERIPHERALS_MOTOR_MOTOR_HPP_

#include "Peripherals/ADC/ADC.hpp"
#include "Peripherals/Timer/Timer.hpp"
#include "Peripherals/Watchdog/Watchdog.hpp"
#include "Peripherals/peripherals.hpp"
#include "main.h"
#include "string.h"
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Motor: public Peripheral {
private:
	Adc &adc;
	Timer &timer;
	Watchdog &watchdog;
	uint32_t analogValue;

public:
	char buffer[4096];
	int motorState = 0;
	Motor(Adc &adc_, Timer &timer_, Watchdog &wdg);
	void Init() override;
	void Start() override;
	void Stop() override;
	void Control(int state);
};
#endif /* __cplusplus */

#endif /* CPP_PERIPHERALS_MOTOR_MOTOR_HPP_ */
