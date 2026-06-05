#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "driver/rmt_tx.h"
#include "led_strip.h"

#define NEOPIXEL_PIN     39
#define NEOPIXEL_POWER   38

extern "C" void app_main(void)
{
    // Power up the NeoPixel
    gpio_set_direction((gpio_num_t)NEOPIXEL_POWER, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)NEOPIXEL_POWER, 1);

    // Configure LED strip
    led_strip_config_t strip_config = {
        .strip_gpio_num = NEOPIXEL_PIN,
        .max_leds = 1,
    };
    led_strip_rmt_config_t rmt_config = {
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
    };
    led_strip_handle_t strip;
    led_strip_new_rmt_device(&strip_config, &rmt_config, &strip);

    while (true) {
        // Red
        led_strip_set_pixel(strip, 0, 16, 0, 0);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Green
        led_strip_set_pixel(strip, 0, 0, 16, 0);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(500));

        // Blue
        led_strip_set_pixel(strip, 0, 0, 0, 16);
        led_strip_refresh(strip);
        vTaskDelay(pdMS_TO_TICKS(500));
    }
}