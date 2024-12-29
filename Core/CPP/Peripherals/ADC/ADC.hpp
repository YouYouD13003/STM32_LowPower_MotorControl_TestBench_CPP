/*
 * ADC.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef CPP_PERIPHERALS_ADC_ADC_HPP_
#define CPP_PERIPHERALS_ADC_ADC_HPP_

#include "stm32l1xx_hal.h"
#include "Peripherals/Watchdog/Watchdog.hpp"

#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Adc {
private:
	ADC_HandleTypeDef &hadc;  // Reference
	Watchdog &watchdog;       // Reference
	uint32_t adcValue;      // Reference

public:
	Adc(ADC_HandleTypeDef &adcHandle, Watchdog &wdg);
	void Init();
	void Start();
	void AdcFunction();
	void Stop();
	uint32_t GetValue();
};
#endif /* __cplusplus */

#endif /* CPP_PERIPHERALS_ADC_ADC_HPP_ */
