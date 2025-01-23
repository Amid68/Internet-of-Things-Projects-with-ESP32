#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "dht.h"

static const dht_sensor_type_t sensor_type = DHT_TYPE_DHT11;
static const gpio_num_t dht_gpio = 26;

void dht_task(void *pvParameter) {
    dht_data_t data;
    
    while(1) {
        if (dht_read(sensor_type, dht_gpio, &data) == ESP_OK) {
            printf("Humidity: %.1f%% Temp: %.1f°C\n", 
                  data.humidity / 10.0, 
                  data.temperature / 10.0);
        } else {
            printf("Sensor read error\n");
        }
        vTaskDelay(pdMS_TO_TICKS(2000));
    }
}

void app_main() {
    xTaskCreate(dht_task, "dht_task", configMINIMAL_STACK_SIZE * 3, NULL, 5, NULL);
}