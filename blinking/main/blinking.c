/**
 * @file blinking.c
 * @brief Sequential LED blinking example for ESP32
 * @details Cycles through 3 LEDs connected to GPIO pins with 1-second interval
 */

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

// GPIO definitions for LED connections
#define LED1 25  ///< GPIO25 for LED 1
#define LED2 26  ///< GPIO26 for LED 2
#define LED3 27  ///< GPIO27 for LED 3

/**
 * @brief Activates specified LED while deactivating others
 * @param led Number of LED to activate (1-3)
 */
void turn_on_led(int led)
{
    // Deactivate all LEDs first
    gpio_set_level(LED1, 0);
    gpio_set_level(LED2, 0);
    gpio_set_level(LED3, 0);

    // Activate selected LED
    switch(led)
    {
        case 1:
            gpio_set_level(LED1, 1);
            break;
        case 2:
            gpio_set_level(LED2, 1);
            break;
        case 3:
            gpio_set_level(LED3, 1);
            break;
    }
}

/**
 * @brief Main task for LED sequence control
 * @param pvParameter Task parameters (unused)
 */
void blinking_task(void *pvParameter)
{
    // Configure GPIO pins as digital outputs
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

    int current_led = 1;
    while(1) {
        turn_on_led(current_led);
        
        // Cycle through LEDs every second
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        current_led = (current_led % 3) + 1; // Maintain 1-3 range
    }
}

/**
 * @brief Main application entry point
 */
void app_main()
{
    // Create FreeRTOS task for LED sequence
    xTaskCreate(&blinking_task,   // Task function
                "blinking_task",  // Task name
                configMINIMAL_STACK_SIZE, // Stack size
                NULL,             // Parameters
                5,                // Priority
                NULL);            // Task handle
}