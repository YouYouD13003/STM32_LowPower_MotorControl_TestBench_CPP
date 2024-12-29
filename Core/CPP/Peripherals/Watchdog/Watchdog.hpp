/*
 * Watchdog.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef CPP_PERIPHERALS_WATCHDOG_WATCHDOG_HPP_
#define CPP_PERIPHERALS_WATCHDOG_WATCHDOG_HPP_

#include "peripherals.hpp"
#include "stm32l1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Watchdog: public Peripheral {
private:
	IWDG_HandleTypeDef &hiwdg;  // Reference to the watchdog handle

public:
	Watchdog(IWDG_HandleTypeDef &iwdgHandle);
	void Init() override;
	void Start() override;
	void Stop() override;
};
#endif /* __cplusplus */

#endif /* CPP_PERIPHERALS_WATCHDOG_WATCHDOG_HPP_ */
