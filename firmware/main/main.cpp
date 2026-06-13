#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "MPU9250Driver.hpp"
#include "EspI2CTransport.hpp"

constexpr uint32_t DELAY_TIME_MS{250};
static const char *TAG = "app";

constexpr gpio_num_t sdaPin{GPIO_NUM_7};
constexpr gpio_num_t sclPin{GPIO_NUM_6};
constexpr uint32_t clockSpeed{400000};
const i2c_port_t i2cPort{I2C_NUM_0};

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

    MPU9250Driver driver{transport};

    if (!driver.init())
    {
        ESP_LOGI(TAG, "Error, could not initialize imu driver");
        abort();
    }

    IIMUDriver& imu = driver;

    while (true)
    {

        accelData = imu.getAccel();
        ESP_LOGI(TAG, "accel x: %.2f", accelData.x);
        ESP_LOGI(TAG, "accel y: %.2f", accelData.y);
        ESP_LOGI(TAG, "accel z: %.2f", accelData.z);

        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
}