/*
 * Motor.cpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#include "Peripherals/Motor/Motor.hpp"

extern UART_HandleTypeDef huart3;

Motor::Motor(Adc &adc_, Timer &timer_, Watchdog &wdg) :
		adc(adc_), timer(timer_), watchdog(wdg), analogValue(0), motorState(0) {
}

void Motor::Init() {
	this->timer.Init();
	this->watchdog.Init();
}

void Motor::Start() {
	this->timer.Start();

	// Obtenir la valeur analogique de l'ADC
	this->analogValue = this->adc.GetValue();

	const uint32_t maxADCValue = 4095; // ADC sur 12 bits
	uint32_t Factor = TIM3->ARR - 1; // Calculer le facteur de PWM

	uint32_t analogValueM = (this->analogValue * Factor) / maxADCValue;

	// Mettre à jour la valeur CCR1 pour contrôler le moteur via PWM
	TIM3->CCR1 = analogValueM;

	// Envoyer les données à l'ESP32 via UART
	snprintf(this->buffer, sizeof(this->buffer), "%lu\r\n", this->analogValue);
	HAL_UART_Transmit(&huart3, (uint8_t*) this->buffer, strlen(this->buffer),
	HAL_MAX_DELAY);
}

void Motor::Stop() {
	TIM3->CCR1 = 0;
	this->timer.Stop();
}

void Motor::Control(int state) {
	this->motorState = state;
	if (this->motorState == 1) {
		this->Start();
	} else {
		this->Stop();
	}
	this->watchdog.Start();
}
