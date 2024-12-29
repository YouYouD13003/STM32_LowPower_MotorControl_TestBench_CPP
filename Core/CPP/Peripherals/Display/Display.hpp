/*
 * Display.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */

#ifndef CPP_DISPLAY_HPP_
#define CPP_DISPLAY_HPP_

#include "Peripherals/peripherals/peripherals.hpp"
#include "stm32l1xx_hal.h"
#include <stdio.h>

#include "max7219.h"
#include "stm32l1xx_hal.h"

#ifdef __cplusplus
extern "C" {
#endif



#ifdef __cplusplus
}
#endif

#ifdef __cplusplus
class Display {
public:
	// Constructor
	Display(SPI_HandleTypeDef &spiHandle, GPIO_TypeDef *ncsPort,
			uint16_t ncsPin);

	// Public methods
	HAL_StatusTypeDef Init();                    // Initialize the display
	void Start();                   // Start the display (clear)
	void Stop();                    // Stop the display (clear digits)
	void DisplayValue(int value);   // Display a value on the 7-segment display

	// New public method declarations
	HAL_StatusTypeDef read_adc_and_display(); // Reads ADC and displays the result
	HAL_StatusTypeDef display_data(unsigned int digits[4]); // Displays the digits on the 7-segment display

private:
	// Private method
	void split_digits(int value, unsigned int digits[4]); // Helper to split integer into digits

	// Member variables
	SPI_HandleTypeDef &hspi;   // SPI handle
	GPIO_TypeDef *ncsPort;     // Chip select port
	uint16_t ncsPin;           // Chip select pin
	MAX7219_Handle_TypeDef max_7219_handle;  // MAX7219 handle
};
#endif /* __cplusplus */

#endif /* CPP_DISPLAY_HPP_ */
