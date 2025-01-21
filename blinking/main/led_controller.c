/**
 * @file led_controller.c
 * @brief Implementation of multi-LED control logic
 */

#include "led_controller.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

static const char *TAG = "LED_CTRL";

#if CONFIG_BLINK_LED_GPIO
// GPIO LED Configuration
static const gpio_num_t led_gpios[] = {
    CONFIG_BLINK_GPIO_1,
    CONFIG_BLINK_GPIO_2,
    CONFIG_BLINK_GPIO_3
};
static bool led_states = false;

#elif CONFIG_BLINK_LED_STRIP
// LED Strip Configuration
static led_strip_handle_t led_strip;
static const uint32_t led_count = CONFIG_BLINK_STRIP_LED_COUNT;

#endif

void led_controller_init(void)
{
#if CONFIG_BLINK_LED_GPIO
    ESP_LOGI(TAG, "Initializing GPIO LEDs on pins %d, %d, %d",
            led_gpios[0], led_gpios[1], led_gpios[2]);
    
    for(int i = 0; i < 3; i++) {
        gpio_reset_pin(led_gpios[i]);
        gpio_set_direction(led_gpios[i], GPIO_MODE_OUTPUT);
    }

#elif CONFIG_BLINK_LED_STRIP
    ESP_LOGI(TAG, "Initializing LED strip with %d LEDs on GPIO %d", 
            led_count, CONFIG_BLINK_STRIP_GPIO);

    led_strip_config_t strip_config = {
        .strip_gpio_num = CONFIG_BLINK_STRIP_GPIO,
        .max_leds = led_count,
    };

    #if CONFIG_BLINK_LED_STRIP_BACKEND_RMT
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000,
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    
    #else
    led_strip_spi_config_t spi_config = {
        .spi_bus = SPI2_HOST,
        .flags.with_dma = true,
    };
    ESP_ERROR_CHECK(led_strip_new_spi_device(&strip_config, &spi_config, &led_strip));
    #endif

    led_strip_clear(led_strip);
#endif
}

void led_controller_update(void)
{
#if CONFIG_BLINK_LED_GPIO
    // Toggle all GPIO LEDs simultaneously
    led_states = !led_states;
    for(int i = 0; i < 3; i++) {
        gpio_set_level(led_gpios[i], led_states);
        ESP_LOGD(TAG, "LED %d set to %s", i+1, led_states ? "ON" : "OFF");
    }

#elif CONFIG_BLINK_LED_STRIP
    // Update all strip LEDs with white color pattern
    static bool strip_state = false;
    const uint8_t intensity = strip_state ? 16 : 0;  // 6% brightness
    
    for(int i = 0; i < led_count; i++) {
        led_strip_set_pixel(led_strip, i, intensity, intensity, intensity);
    }
    led_strip_refresh(led_strip);
    strip_state = !strip_state;
    ESP_LOGD(TAG, "Strip LEDs updated to %s", strip_state ? "ON" : "OFF");
#endif
}