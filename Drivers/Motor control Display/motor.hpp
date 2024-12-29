/*
 * motor.hpp
 *
 *  Created on: Oct 16, 2024
 *      Author: Ayoub
 */



// motor.hpp

#ifndef MOTOR_HPP
#define MOTOR_HPP

#include "stm32l1xx_hal.h"
#include <stdio.h>
#include <stdlib.h>

class MotorControl {
private:
    // Private variables
    ADC_HandleTypeDef* adc;
    TIM_HandleTypeDef* timer3;
    TIM_HandleTypeDef* timer6;
    IWDG_HandleTypeDef* watchdog;

    volatile int flag_irq;
    volatile int GotoSleep;
    uint8_t WatchdogStatus;
    uint32_t analogValue;

    unsigned int a1, a2, a3, a4;  // Temporary variables for ADC value digits
    int motorState;

    // Private helper functions
    void splitData(int adc_value);
    HAL_StatusTypeDef displayData();
    HAL_StatusTypeDef readAdcAndDisplay();

public:
    // Constructor
    MotorControl(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim3, TIM_HandleTypeDef* htim6, IWDG_HandleTypeDef* hiwdg);

    // Public methods
    void adcFunction();
    void motor(int motorState);
    void motorSpeed();
    void handleSleep();
    void motorControl();

    // Interrupt handler
    void handleInterrupt(uint16_t GPIO_Pin);

    // Timer callback
    void handleTimerInterrupt(TIM_HandleTypeDef* htim);
};

#endif // MOTOR_HPP


