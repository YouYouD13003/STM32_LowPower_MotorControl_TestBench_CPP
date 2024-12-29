/*
 * Watchdog.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#include "Peripherals/Watchdog/Watchdog.hpp"

Watchdog::Watchdog(IWDG_HandleTypeDef &iwdgHandle) :
		hiwdg(iwdgHandle) {
}

void Watchdog::Init() {
	HAL_IWDG_Init(&hiwdg);
}

void Watchdog::Start() {
	HAL_IWDG_Refresh(&hiwdg);
}

void Watchdog::Stop() {
// not possible
}
