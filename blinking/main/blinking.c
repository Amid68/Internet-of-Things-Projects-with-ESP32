#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#define LED1 25
#define LED2 26
#define LED3 27

void turn_on_led(int led)
{
    // turn off all leds
    gpio_set_level(LED1, 0);
    gpio_set_level(LED2, 0);
    gpio_set_level(LED3, 0);

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

void blinking_task(void *pvParameter)
{
    gpio_set_direction(LED1, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED2, GPIO_MODE_OUTPUT);
    gpio_set_direction(LED3, GPIO_MODE_OUTPUT);

    int current_led = 1;
    while(1) {
        turn_on_led(current_led);
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        
        current_led++;
        if(current_led>3)
            current_led = 1;
    }
}

void app_main()
{
    xTaskCreate(&blinking_task, "blinking_task", configMINIMAL_STACK_SIZE, NULL, 5, NULL);
}