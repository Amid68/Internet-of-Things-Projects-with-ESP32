/**
 * @file led_controller.h
 * @brief Multi-LED control interface for ESP32-WROOM-32E
 */

#pragma once
#include <stdbool.h>
#include "driver/gpio.h"
#include "led_strip.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initialize LED control hardware
 * 
 * Configures GPIOs or LED strip based on Kconfig settings
 */
void led_controller_init(void);

/**
 * @brief Update LED states according to current pattern
 * 
 * Toggles LED states and handles refresh timing
 */
void led_controller_update(void);

#ifdef __cplusplus
}
#endif