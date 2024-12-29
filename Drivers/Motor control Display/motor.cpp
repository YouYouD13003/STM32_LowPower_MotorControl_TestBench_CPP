///*
// * motor.cpp
// *
// *  Created on: Oct 16, 2024
// *      Author: Ayoub
// */
//
//
///// main.cpp
//// motor.cpp
//
//#include "motor.hpp"
//
//MotorControl::MotorControl(ADC_HandleTypeDef* hadc, TIM_HandleTypeDef* htim3, TIM_HandleTypeDef* htim6, IWDG_HandleTypeDef* hiwdg)
//    : adc(hadc), timer3(htim3), timer6(htim6), watchdog(hiwdg), flag_irq(0), GotoSleep(0), WatchdogStatus(RESET), analogValue(0), motorState(0) { }
//
//void MotorControl::adcFunction() {
//    HAL_ADC_Start(adc);
//    HAL_StatusTypeDef status = HAL_ADC_PollForConversion(adc, 1000);
//    if (status != HAL_OK) {
//        Error_Handler();
//    }
//    analogValue = HAL_ADC_GetValue(adc);
//    HAL_ADC_Stop(adc);
//    HAL_TIM_Base_Start_IT(timer6);
//
//    if (flag_irq == 1) {
//        flag_irq = 0;
//        const uint16_t thresholds[] = { 0, 300, 511, 1023, 2047, 2400, 2600, 2800, 2900 };
//        const uint16_t pins[] = { GPIO_PIN_0, GPIO_PIN_1, GPIO_PIN_2, GPIO_PIN_10, GPIO_PIN_11, GPIO_PIN_12, GPIO_PIN_13, GPIO_PIN_14, GPIO_PIN_15 };
//        const int numThresholds = sizeof(thresholds) / sizeof(thresholds[0]);
//
//        for (int i = 0; i < numThresholds; i++) {
//            if (analogValue > thresholds[i]) {
//                HAL_GPIO_WritePin(GPIOB, pins[i], GPIO_PIN_SET);
//            } else {
//                HAL_GPIO_WritePin(GPIOB, pins[i], GPIO_PIN_RESET);
//            }
//        }
//    }
//}
//
//void MotorControl::motor(int state) {
//    HAL_StatusTypeDef status;
//    if (state == 1) {
//        status = HAL_TIM_Base_Start_IT(timer3);
//        if (status != HAL_OK) {
//            Error_Handler();
//            return;
//        }
//        status = HAL_TIM_PWM_Start_IT(timer3, TIM_CHANNEL_1);
//        if (status != HAL_OK) {
//            Error_Handler();
//            return;
//        }
//    } else {
//        status = HAL_TIM_Base_Stop_IT(timer3);
//        if (status != HAL_OK) {
//            Error_Handler();
//            return;
//        }
//        status = HAL_TIM_PWM_Stop_IT(timer3, TIM_CHANNEL_1);
//        if (status != HAL_OK) {
//            Error_Handler();
//            return;
//        }
//    }
//
//    if (HAL_IWDG_Refresh(watchdog) != HAL_OK) {
//        Error_Handler();
//    }
//}
//
//void MotorControl::motorSpeed() {
//    analogValue = HAL_ADC_GetValue(adc);
//    const uint32_t maxADCValue = 4095; // 12-bit ADC
//    uint32_t Factor = timer3->Instance->ARR - 1;
//    uint32_t analogValueM = (analogValue * Factor) / maxADCValue;
//    timer3->Instance->CCR1 = analogValueM;
//}
//
//void MotorControl::splitData(int adc_value) {
//    a1 = adc_value / 1000;
//    a2 = (adc_value / 100) % 10;
//    a3 = (adc_value / 10) % 10;
//    a4 = adc_value % 10;
//}
//
//HAL_StatusTypeDef MotorControl::displayData() {
//    HAL_StatusTypeDef status = HAL_OK;
//    unsigned int digits[4] = { a1, a2, a3, a4 };
//    unsigned char binary_pattern[] = { 0x7E, 0x30, 0x6D, 0x79, 0x33, 0x5B, 0x5F, 0x70, 0x7F, 0x7B };
//
//    for (int i = 0; i < 4; i++) {
//        if (digits[i] < 0 || digits[i] > 9) {
//            return HAL_ERROR;
//        }
//        unsigned char pattern = binary_pattern[digits[i]];
//        status = max7219_display_no_decode(i, pattern);
//        if (status != HAL_OK) {
//            Error_Handler();
//            return status;
//        }
//    }
//
//    if (status == HAL_OK && HAL_IWDG_Refresh(watchdog) != HAL_OK) {
//        return HAL_ERROR;
//    }
//
//    return HAL_OK;
//}
//
//HAL_StatusTypeDef MotorControl::readAdcAndDisplay() {
//    if (HAL_ADC_Start(adc) != HAL_OK) {
//        HAL_ADC_Stop(adc);
//        return HAL_ERROR;
//    }
//
//    if (HAL_ADC_PollForConversion(adc, 1000) == HAL_OK) {
//        int adc_value = HAL_ADC_GetValue(adc);
//        splitData(adc_value);
//        return displayData();
//    } else {
//        HAL_ADC_Stop(adc);
//        return HAL_ERROR;
//    }
//
//    HAL_ADC_Stop(adc);
//    if (HAL_IWDG_Refresh(watchdog) != HAL_OK) {
//        return HAL_ERROR;
//    }
//    return HAL_OK;
//}
//
//void MotorControl::handleInterrupt(uint16_t GPIO_Pin) {
//    switch (GPIO_Pin) {
//    case GPIO_PIN_11:
//        HAL_PWR_DisableSleepOnExit();
//        HAL_ResumeTick();
//        break;
//    case GPIO_PIN_12:
//        motorState = !motorState;
//        motor(motorState);
//        break;
//    case GPIO_PIN_6:
//        GotoSleep = 1;
//        break;
//    default:
//        break;
//    }
//}
//
//void MotorControl::handleTimerInterrupt(TIM_HandleTypeDef* htim) {
//    if (htim->Instance == timer6->Instance) {
//        flag_irq = 1;
//    }
//}
