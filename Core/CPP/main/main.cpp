#include "main.hpp"
#include "main.h"
#include "Peripherals/Motor/Motor.hpp"
#include "Peripherals/Display/Display.hpp"
#include "Peripherals/ADC/ADC.hpp"
#include "Peripherals/Timer/Timer.hpp"
#include "max7219.h"
#include "Peripherals/Watchdog/Watchdog.hpp"
#include "stm32l1xx_hal.h"
//Ayoub ABBES
extern ADC_HandleTypeDef hadc;
extern TIM_HandleTypeDef htim3;
extern IWDG_HandleTypeDef hiwdg;
extern TIM_HandleTypeDef htim6;
extern SPI_HandleTypeDef hspi1;

volatile int flag_irq = 0;
uint8_t WatchdogStatus = RESET;
extern int motorState;
volatile int GotoSleep = 0;
volatile int test_io = 0;

// Initialize the objects for peripherals
Timer PWM_Timer(htim3, TIM_CHANNEL_1);  // PWM channel for timer
Watchdog watchdog(hiwdg);               // Watchdog object
Adc adc(hadc, watchdog);                // ADC object with Watchdog
Motor motor(adc, PWM_Timer, watchdog);  // Motor object
Display display(hspi1, NCS_GPIO_Port, NCS_Pin);
Timer basicTimer(htim6);                // Basic timer

// Create TestBench object with all peripherals
TestBench testBench(motor, display, adc, basicTimer, PWM_Timer, watchdog);

int _write(int file, char *ptr, int len) {
	for (int DataIdx = 0; DataIdx < len; DataIdx++) {
		ITM_SendChar(*ptr++);  // Send data for debugging
	}
	return len;
}

// TestBench class methods
TestBench::TestBench(Motor &motor_, Display &display_, Adc &adc_,
		Timer &basicTimer_, Timer &PWM_Timer_, Watchdog &watchdog_) :
		motor(motor_), display(display_), adc(adc_), basicTimer(basicTimer_), PWM_Timer(
				PWM_Timer_), watchdog(watchdog_) {
}

// Initialize all peripherals
void TestBench::initialize_peripherals() {
	adc.Init();          // Initialize ADC
	basicTimer.Init();   // Initialize basic timer
	PWM_Timer.Init();    // Initialize PWM Timer
	watchdog.Init();     // Initialize Watchdog
	motor.Init();        // Initialize Motor
	display.Init();      // Initialize Display
}

// Run the Test Bench operations
void TestBench::run() {
	display.read_adc_and_display();  // Update display based on ADC value
	adc.AdcFunction();  // ADC function manages LEDs
	motor.Control(motor.motorState);  // Control motor based on ADC values
	sleep();  // Call the sleep function to handle sleep mode
}

// Handle sleep mode
void TestBench::sleep() {
	if (GotoSleep == 1) {
		GotoSleep = 0;
		for (int i = 0; i < 4; i++) {
			max7219_display_no_decode(i, 0x00);  // Clear display
		}

		HAL_SuspendTick(); // Suspend Tick increment to prevent wake up from SysTick interrupt
		HAL_PWR_EnableSleepOnExit();  // Enter sleep mode on exit from interrupt
		HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI); // Enter sleep mode
		HAL_ResumeTick();  // Resume Tick increment after wake-up
	}
}

// Main loop
void main_cpp(void) {
	testBench.initialize_peripherals();  // Initialize all peripherals
	basicTimer.Start();         // Start the basic timer
	PWM_Timer.Start();          // Start the PWM Timer

	while (1) {
		testBench.run();  // Use the TestBench class to run operations
	}
}

// Interrupt for button press handling
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	switch (GPIO_Pin) {
	case GPIO_PIN_11:  // BTN1 wake-up pin
		HAL_PWR_DisableSleepOnExit();
		HAL_ResumeTick();
		break;

	case GPIO_PIN_12:  // BTN2 ON/OFF
		motor.motorState = (motor.motorState == 0) ? 1 : 0;
		break;

	case GPIO_PIN_6:  // BTN3 wake up pin after putting the system to sleep
		GotoSleep = 1;
		break;

	default:
		break;
	}
}

// ADC watchdog callback for out-of-window events
extern "C" void HAL_ADC_LevelOutOfWindowCallback(ADC_HandleTypeDef *hadc) {
	WatchdogStatus = SET;

	if (WatchdogStatus == SET) {
		motor.motorState = 0;
		motor.Control(0);  // Stop the motor in case of a watchdog event
	}

	WatchdogStatus = RESET;
}

// Timer interrupt callback
extern "C" void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == TIM6) {
		flag_irq = 1;
		printf("TIMER triggered\n");  // Debug output for the timer trigger
	}
}
