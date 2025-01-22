/**
 * @file blinking_sequence.c
 * @brief LED pattern sequence controller implementation
 * @details Concrete implementation of timed LED cycling logic
 * 
 * @author Ameed Othman
 * @date 22/01/2025
 */
#include "blinking_sequence.h"
#include "led_controller.h"

static void blinking_task(void *pvParameter) {
    led_controller_init();
    
    uint8_t current_led = 1;
    while(1) {
        led_all_off();
        led_set_state(current_led, 1);
        
        vTaskDelay(pdMS_TO_TICKS(1000));
        current_led = (current_led % 3) + 1;
    }
}

TaskHandle_t blinking_sequence_create(void) {
    TaskHandle_t task_handle;
    xTaskCreate(blinking_task,         // Task function
                "blinking_sequence",   // Task name
                2048,                  // Stack size
                NULL,                  // Parameters
                tskIDLE_PRIORITY + 1,  // Priority
                &task_handle);         // Task handle
    return task_handle;
}