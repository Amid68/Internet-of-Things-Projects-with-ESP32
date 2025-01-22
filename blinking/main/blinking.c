/**
 * @file blinking.c
 * @brief Sequential LED blinking example for ESP32
 * @details Cycles through 3 LEDs connected to GPIO pins with 1-second interval
 * 
 * @author Ameed Othman
 * @date 22/01/2025
 */

#include "blinking_sequence.h"

void app_main() {
    TaskHandle_t blink_task = blinking_sequence_create();
}