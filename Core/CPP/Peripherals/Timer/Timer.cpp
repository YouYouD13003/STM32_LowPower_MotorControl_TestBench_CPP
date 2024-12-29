#include "Peripherals/Timer/Timer.hpp"

// Constructor for timers without PWM channels
Timer::Timer(TIM_HandleTypeDef &timHandle) :
		htim(timHandle), channel(0), hasChannel(false) {
}

// Constructor for timers with PWM channels
Timer::Timer(TIM_HandleTypeDef &timHandle, uint32_t pwmChannel) :
		htim(timHandle), channel(pwmChannel), hasChannel(true) {
}

void Timer::Init() {
	HAL_TIM_Base_Init(&this->htim); // Utilisation de this-> pour accéder aux membres de la classe
	if (this->hasChannel) {
		// Initialiser PWM si un canal est présent
		HAL_TIM_PWM_Init(&this->htim);
	}
}

void Timer::Start() {
	HAL_TIM_Base_Start_IT(&this->htim);
	if (this->hasChannel) {
		// Démarrer le PWM si applicable
		HAL_TIM_PWM_Start_IT(&this->htim, this->channel);
	}
}

void Timer::Stop() {
	HAL_TIM_Base_Stop_IT(&this->htim);
	if (this->hasChannel) {
		// Stopper le PWM si applicable
		HAL_TIM_PWM_Stop_IT(&this->htim, this->channel);
	}
}

void Timer::SetPWM(uint32_t value) {
	if (this->hasChannel) {
		__HAL_TIM_SET_COMPARE(&this->htim, this->channel, value);
	} else {
		// Gérer le cas où SetPWM est appelé sur un timer sans canal PWM
		printf("Error: Timer does not have a PWM channel.\n");
	}
}
