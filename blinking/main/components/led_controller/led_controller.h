/**
 * @file led_controller.h
 * @brief LED hardware abstraction layer interface
 * @details GPIO configuration and control functions for LED management
 * 
 * @author Ameed Othman
 * @date 22/01/2025
 */
#pragma once
#include <stdint.h>

/**
 * @brief Initialize LED GPIO configuration
 */
void led_controller_init(void);

/**
 * @brief Control LED states
 * @param led_num LED number (1-3)
 * @param state 0=OFF, 1=ON
 */
void led_set_state(uint8_t led_num, uint8_t state);

/**
 * @brief Turn off all LEDs
 */
void led_all_off(void);