# STM32_LowPower_MotorControl_TestBench_CPP
A modular motor control test bench using an 
STM32 microcontroller programmed in C++. 
Key features include:  
Low Power Management: Sleep mode can be triggered and exited via specific push buttons.
Motor Control: ADC readings from a potentiometer are converted to PWM signals, controlling motor speed proportionally. 
Real-Time Display: ADC values are continuously displayed on a 7-segment display (SPI interface). 
Visual Feedback: LEDs light up in 7 levels corresponding to different ADC ranges.
Safety Mechanisms: Includes a software watchdog and an ADC watchdog for system reliability. 
Interrupts for Push Buttons: Ensures responsive control for motor ON/OFF and wake-up functionality. 
Timers: Used for precise PWM generation and timing operations. 
UART Communication: ADC values are transmitted to an ESP32, which hosts a Wi-Fi-based webserver for real-time monitoring. 
Designed for educational purposes, this project simulates real-world industrial control systems while prioritizing efficiency and modularity.
