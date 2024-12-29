#include "Peripherals/ADC/ADC.hpp"
#include <stdio.h>
#include <stdlib.h>
#include "main.h"

#define ADC_BUF_LEN 4096
extern TIM_HandleTypeDef htim6;
extern int flag_irq;
uint16_t adc_buf[ADC_BUF_LEN];

Adc::Adc(ADC_HandleTypeDef &adcHandle, Watchdog &wdg) :
		hadc(adcHandle), watchdog(wdg), adcValue(0) {
	printf("ADC constructor called\n");
}

void Adc::Init() {
	printf("Initializing ADC...\n");
	if (HAL_ADC_Init(&this->hadc) != HAL_OK) { // Utilisation de this-> pour accéder aux membres de la classe
		printf("ADC initialization error!\n");
		Error_Handler();
	} else {
		printf("ADC initialized successfully.\n");
	}
}

void Adc::Start() {
	printf("Starting ADC...\n");
	if (HAL_ADC_Start(&this->hadc) != HAL_OK) {
		printf("ADC start error!\n");
		Error_Handler();
	}
}

void Adc::Stop() {
	printf("Stopping ADC...\n");
	if (HAL_ADC_Stop(&this->hadc) != HAL_OK) {
		printf("ADC stop error!\n");
		Error_Handler();
	}
}

uint32_t Adc::GetValue() {
	this->adcValue = HAL_ADC_GetValue(&this->hadc);
	printf("ADC value read: %lu\n", this->adcValue);
	return this->adcValue;
}

void Adc::AdcFunction() {
	// Utilisation de this-> pour la clarté et l'accès aux membres de la classe
	this->Start();

	HAL_StatusTypeDef status = HAL_ADC_PollForConversion(&this->hadc, 1000);
	if (status == HAL_OK) {
		this->watchdog.Start();
		this->GetValue();

		// Logique pour les seuils et les LEDs
		const uint16_t thresholds[] = { 0, 300, 511, 1023, 2047, 2400, 2600,
				2800, 2900 };
		const uint16_t pins[] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2,
		GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12,
		GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 };
		const int numThresholds = sizeof(thresholds) / sizeof(thresholds[0]);

		for (int i = 0; i < numThresholds; i++) {
			if (this->adcValue > thresholds[i]) {
				HAL_GPIO_WritePin(GPIOB, pins[i], GPIO_PIN_SET); // Allumer la LED
			} else {
				HAL_GPIO_WritePin(GPIOB, pins[i], GPIO_PIN_RESET); // Éteindre la LED
			}
		}
	} else {
		printf("ADC conversion error!\n");
		Error_Handler();
	}
}
