#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "led_strip.h"

#define NEOPIXEL_PIN    39
#define NEOPIXEL_POWER  38

constexpr size_t DELAY_TIME_MS{1000};

extern "C" void app_main(void)
{
    // Power up the NeoPixel
    gpio_set_direction((gpio_num_t)NEOPIXEL_POWER, GPIO_MODE_OUTPUT);
    gpio_set_level((gpio_num_t)NEOPIXEL_POWER, 1);

    // Configure LED strip
    led_strip_config_t strip_config = {};
    strip_config.strip_gpio_num = NEOPIXEL_PIN;
    strip_config.max_leds = 1;

    led_strip_rmt_config_t rmt_config = {};
    rmt_config.resolution_hz = 10 * 1000 * 1000; // 10MHz

    led_strip_handle_t strip;
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &strip));

    while (true) {
        // // Red
        // ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, 16, 0, 0));
        // ESP_ERROR_CHECK(led_strip_refresh(strip));
        // vTaskDelay(pdMS_TO_TICKS(500));

        // // Green
        // ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, 0, 16, 0));
        // ESP_ERROR_CHECK(led_strip_refresh(strip));
        // vTaskDelay(pdMS_TO_TICKS(500));

        // // Blue
        // ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, 0, 0, 16));
        // ESP_ERROR_CHECK(led_strip_refresh(strip));
        // vTaskDelay(pdMS_TO_TICKS(500));

        // White
        ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, 16, 16, 16));
        ESP_ERROR_CHECK(led_strip_refresh(strip));
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));

        ESP_ERROR_CHECK(led_strip_set_pixel(strip, 0, 0, 0, 0));
        ESP_ERROR_CHECK(led_strip_refresh(strip));
        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
}