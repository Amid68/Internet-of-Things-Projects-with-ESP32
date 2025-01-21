#include "led_controller.h"
#include "esp_log.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"

void app_main(void)
{
    led_controller_init();
    
    while(1) {
        led_controller_update();
        vTaskDelay(pdMS_TO_TICKS(CONFIG_BLINK_PERIOD_MS));
    }
}