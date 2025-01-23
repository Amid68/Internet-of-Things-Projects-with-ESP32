#include "dht.h"
#include "esp_log.h"
#include "esp_timer.h"
#include "esp_rom_sys.h"
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#define TAG "DHT"

// Timing constants
#define DHT_TIMEOUT 1000
#define DHT_START_TIME 18000
#define DHT_EDGE_WAIT 40
#define DHT_SAMPLE_INTERVAL 2000

static esp_err_t wait_for_level(gpio_num_t gpio, uint32_t timeout_us, int expected_level) {
    uint32_t start = esp_timer_get_time();
    while (gpio_get_level(gpio) != expected_level) {
        if (esp_timer_get_time() - start > timeout_us) {
            return ESP_ERR_TIMEOUT;
        }
        esp_rom_delay_us(1);
    }
    return ESP_OK;
}

static esp_err_t read_data(gpio_num_t gpio, uint8_t *data) {
    // Read 40 bits (5 bytes)
    for (int i = 0; i < 40; i++) {
        // Wait for falling edge
        ESP_ERROR_CHECK(wait_for_level(gpio, DHT_EDGE_WAIT, 0));
        esp_rom_delay_us(30); // Wait 30μs after falling edge
        
        // Measure high pulse duration
        uint32_t start = esp_timer_get_time();
        ESP_ERROR_CHECK(wait_for_level(gpio, DHT_EDGE_WAIT, 1));
        uint32_t duration = esp_timer_get_time() - start;
        
        data[i/8] <<= 1;
        if (duration > 40) { // 26-28μs = 0, 70μs = 1
            data[i/8] |= 1;
        }
    }
    return ESP_OK;
}

esp_err_t dht_read(dht_sensor_type_t type, gpio_num_t gpio_num, dht_data_t *data) {
    static uint32_t last_read_time = UINT32_MAX - (DHT_SAMPLE_INTERVAL * 1000);
    uint32_t current_time = esp_timer_get_time();
    
    if (current_time - last_read_time < DHT_SAMPLE_INTERVAL * 1000) {
        ESP_LOGE(TAG, "Polled too soon");
        return ESP_ERR_INVALID_STATE;
    }
    last_read_time = current_time;

    uint8_t raw_data[5] = {0};
    
    // Configure GPIO
    gpio_set_direction(gpio_num, GPIO_MODE_OUTPUT_OD);
    gpio_set_level(gpio_num, 1);
    esp_rom_delay_us(40);
    
    // Send start signal
    gpio_set_level(gpio_num, 0);
    esp_rom_delay_us(DHT_START_TIME);
    gpio_set_level(gpio_num, 1);
    
    // Switch to input
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT);
    
    // Wait for sensor response
    ESP_ERROR_CHECK(wait_for_level(gpio_num, DHT_TIMEOUT, 0));
    ESP_ERROR_CHECK(wait_for_level(gpio_num, DHT_TIMEOUT, 1));
    ESP_ERROR_CHECK(wait_for_level(gpio_num, DHT_TIMEOUT, 0));

    // Read data
    ESP_ERROR_CHECK(read_data(gpio_num, raw_data));

    // Verify checksum
    if (raw_data[4] != ((raw_data[0] + raw_data[1] + raw_data[2] + raw_data[3]) & 0xFF)) {
        ESP_LOGE(TAG, "Checksum error");
        return ESP_ERR_INVALID_CRC;
    }

    // Convert data
    if (type == DHT_TYPE_DHT11) {
        data->humidity = raw_data[0] * 10;
        data->temperature = raw_data[2] * 10;
    } else { // DHT22
        data->humidity = (raw_data[0] << 8 | raw_data[1]);
        data->temperature = (raw_data[2] << 8 | raw_data[3]);
    }

    // Handle negative temperatures
    if (data->temperature & 0x8000) {
        data->temperature = -(data->temperature & 0x7FFF);
    }

    return ESP_OK;
}