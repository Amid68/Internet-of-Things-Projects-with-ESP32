/**
 * @file led_controller.c
 * @brief LED hardware abstraction layer implementation
 * @details Concrete GPIO operations for LED control on ESP32
 * 
 * @author Ameed Othman
 * @date 22/01/2025
 */
#include "led_controller.h"
#include "driver/gpio.h"

// LED GPIO mappings
#define LED1_GPIO  25
#define LED2_GPIO  26
#define LED3_GPIO  27

void led_controller_init(void) {
    gpio_config_t io_conf = {
        .pin_bit_mask = (1ULL << LED1_GPIO) | (1ULL << LED2_GPIO) | (1ULL << LED3_GPIO),
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&io_conf);
}

void led_set_state(uint8_t led_num, uint8_t state) {
    switch(led_num) {
        case 1: gpio_set_level(LED1_GPIO, state); break;
        case 2: gpio_set_level(LED2_GPIO, state); break;
        case 3: gpio_set_level(LED3_GPIO, state); break;
    }
}

void led_all_off(void) {
    gpio_set_level(LED1_GPIO, 0);
    gpio_set_level(LED2_GPIO, 0);
    gpio_set_level(LED3_GPIO, 0);
}