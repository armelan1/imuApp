#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "IMUDriver.hpp"
#include "EspI2CTransport.hpp"

constexpr uint32_t DELAY_TIME_MS{500};
static const char *TAG = "IMUDriver";

constexpr gpio_num_t sdaPin{GPIO_NUM_7};
constexpr gpio_num_t sclPin{GPIO_NUM_6};
constexpr uint32_t clockSpeed{400000};
const i2c_port_t i2cPort{I2C_NUM_0};

constexpr uint8_t DEV_ADDR{0x68};
constexpr uint8_t WHO_AM_I{0x75};

extern "C" void
app_main(void)
{
    imu::AccelData accelData{};
    EspI2CTransport transport{sdaPin, sclPin, clockSpeed, i2cPort};

    if (!transport.init())
    {
        ESP_LOGI(TAG, "Error, could not initialize i2c driver");
        abort();
    }

    IMUDriver myIMU{transport};

    if (!myIMU.init())
    {
        ESP_LOGI(TAG, "Error, could not initialize imu driver");
        abort();
    }

    constexpr size_t SIZE{1};
    uint8_t data[SIZE];

    while (true)
    {

        if(!transport.read(DEV_ADDR, WHO_AM_I, data, SIZE))
        {
            ESP_LOGI(TAG, "Error, could not read imu id register");
            abort();
        }
        ESP_LOGI(TAG, "WHO_AM_I: 0x%02X", *data);

        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
}