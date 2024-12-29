# STM32 Low Power Motor Control Test Bench

A modular motor control test bench using an STM32 microcontroller, programmed in **C++**. This project simulates a real-world industrial control system, combining efficiency, modularity, and reliability.

## Features

- **Low Power Management**
  - Sleep mode can be triggered by a push button and exited via a wake-up button.

- **Motor Control**
  - ADC readings from a potentiometer are converted into PWM signals to control motor speed proportionally.

- **Real-Time Display**
  - ADC values are continuously displayed on a 7-segment display using the SPI interface.

- **Visual Feedback**
  - LEDs light up in 7 levels corresponding to specific ADC value ranges.

- **Safety Mechanisms**
  - Includes both a **software watchdog** and an **ADC watchdog** for system reliability.

- **Interrupts for Push Buttons**
  - Responsive push buttons control motor ON/OFF and wake-up functionality via external interrupts.

- **Timers**
  - Used for PWM generation and precise timing operations.

- **UART Communication**
  - ADC values are transmitted via UART to an ESP32, which hosts a Wi-Fi web server for real-time monitoring.

## Architecture

The project leverages object-oriented programming principles for modularity. It includes classes for peripherals such as `Motor`, `ADC`, `Timer`, `Display`, `Watchdog`, and others, ensuring clean and maintainable code.

### Hardware Components
- **STM32 Microcontroller**
- **ESP32**: Hosts the web server and displays ADC values via Wi-Fi.
- **Potentiometer**: Used to control motor speed.
- **Push Buttons**: For motor ON/OFF, sleep mode, and wake-up functionality.
- **7-Segment Display**: Displays ADC values in real-time.
- **LED Indicators**: Provide visual feedback for ADC levels.

## Software Stack
- **Programming Language**: C++
- **Communication Protocols**: UART, SPI
- **RTOS Features**: Low power and interrupt handling

## How to Use
1. **Setup the Hardware:**
   - Connect the potentiometer, push buttons, 7-segment display, and LEDs to the STM32.
   - Connect the STM32 to the ESP32 via UART.

2. **Program the STM32:**
   - Flash the provided firmware using your preferred STM32 IDE (CubeIDE or others).

3. **Program the ESP32:**
   - Use an ESP32-compatible IDE to upload the web server code for real-time monitoring.

4. **Run the System:**
   - Power on the STM32 and ESP32.
   - Adjust the potentiometer to control the motor.
   - View ADC values and motor state on the 7-segment display and the web interface.

## System Diagram

```plaintext
+------------+       UART      +-----------+       Wi-Fi       +-------------+
|   STM32    | <-------------> |   ESP32   | <---------------> | Web Server  |
+------------+                 +-----------+                   +-------------+
     |                              |
 [Potentiometer]              [Wi-Fi Antenna]
     |
 [7-Segment Display]
     |
    [LEDs]

