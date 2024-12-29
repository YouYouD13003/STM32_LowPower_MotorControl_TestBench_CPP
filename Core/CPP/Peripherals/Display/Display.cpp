#include "Peripherals/Display/Display.hpp"
#include "max7219.h"
#include "main.h"

extern IWDG_HandleTypeDef hiwdg;
extern ADC_HandleTypeDef hadc;

Display::Display(SPI_HandleTypeDef &spiHandle, GPIO_TypeDef *ncsPort,
		uint16_t ncsPin) :
		hspi(spiHandle), ncsPort(ncsPort), ncsPin(ncsPin) {

	// Utilisation de this-> pour plus de clarté
	this->max_7219_handle.hspi = &this->hspi;
	this->max_7219_handle.spi_ncs_port = this->ncsPort;
	this->max_7219_handle.spi_ncs_pin = this->ncsPin;
	this->max_7219_handle.digits_count = 4;

	printf("Display constructor called\n");
}

HAL_StatusTypeDef Display::Init() {
	printf("Setting up SPI\n");

	HAL_StatusTypeDef InitSPI = max7219_init(&this->max_7219_handle);

	if (InitSPI != HAL_OK) {
		printf("SPI error\n");
		Error_Handler();
		return HAL_ERROR;
	} else {
		printf("SPI OK\n");
		return HAL_OK;
	}
}

void Display::Start() {
	for (int i = 0; i < 4; i++) {
		max7219_display_no_decode(i, 0xFF);
	}
}

void Display::Stop() {
	for (int i = 0; i < 4; i++) {
		max7219_display_no_decode(i, 0x00);
	}
}

void Display::DisplayValue(int value) {
	for (int i = 0; i < 4; i++) {
		int digit = value % 10;
		max7219_display_no_decode(i, digit);
		value /= 10;
	}
}

HAL_StatusTypeDef Display::display_data(unsigned int digits[4]) {
	HAL_StatusTypeDef status = HAL_OK;
	unsigned char binary_pattern[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F,
			0x70, 0x7F, 0x7B };

	for (int i = 0; i < 4; i++) {
		if (digits[i] > 9) {
			return HAL_ERROR;
		}
		unsigned char pattern = binary_pattern[digits[i]];
		status = max7219_display_no_decode(i, pattern);
		if (status != HAL_OK) {
			return status;
		}
	}

	return status;
}

HAL_StatusTypeDef Display::read_adc_and_display() {
	HAL_StatusTypeDef status;

	// Démarrer la conversion ADC
	if (HAL_ADC_Start(&hadc) != HAL_OK) {
		HAL_ADC_Stop(&hadc);
		return HAL_ERROR;
	}

	// Attendre la fin de la conversion
	if (HAL_ADC_PollForConversion(&hadc, 1000) == HAL_OK) {

		int adc_value = HAL_ADC_GetValue(&hadc);

		// Fractionner la valeur ADC en chiffres
		unsigned int digits[4];
		this->split_digits(adc_value, digits);

		// Afficher les chiffres
		status = this->display_data(digits);
		if (status != HAL_OK) {
			HAL_ADC_Stop(&hadc);
			return status;
		}
	} else {
		HAL_ADC_Stop(&hadc);
		return HAL_ERROR;
	}

	// Stopper l'ADC après l'opération
	HAL_ADC_Stop(&hadc);

	// Rafraîchir le Watchdog
	if (HAL_IWDG_Refresh(&hiwdg) != HAL_OK) {
		return HAL_ERROR;
	}

	return HAL_OK;
}

void Display::split_digits(int value, unsigned int digits[4]) {
	for (int i = 3; i >= 0; i--) {
		digits[i] = value % 10;
		value /= 10;
	}
}
