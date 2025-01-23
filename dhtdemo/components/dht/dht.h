#pragma once
#include <stdint.h>
#include "driver/gpio.h"

typedef enum {
    DHT_TYPE_DHT11 = 0,
    DHT_TYPE_DHT22
} dht_sensor_type_t;

typedef struct {
    int16_t temperature;
    int16_t humidity;
} dht_data_t;

esp_err_t dht_read(dht_sensor_type_t type, gpio_num_t gpio_num, dht_data_t *data);