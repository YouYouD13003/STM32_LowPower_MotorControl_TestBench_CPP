/*
 * Timer.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef TIMER_HPP_
#define TIMER_HPP_

#include "main.h"  // Include HAL library to access TIM_HandleTypeDef
#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

// C code (if any) can be placed here.

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Timer {
private:
	TIM_HandleTypeDef &htim;
	uint32_t channel;      // PWM channel, if applicable
	bool hasChannel;       // Flag to determine if the timer uses a PWM channel

public:
	// Constructor for timers without PWM channels //
	Timer(TIM_HandleTypeDef &timHandle);

	// Constructor for timers with PWM channels
	Timer(TIM_HandleTypeDef &timHandle, uint32_t pwmChannel);

	void Init();
	void Start();
	void Stop();
	void SetPWM(uint32_t value);  // Only applicable for timers with channels
};
#endif /* __cplusplus */

#endif /* TIMER_HPP_ */
