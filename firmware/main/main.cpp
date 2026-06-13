#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "IMUDriver.hpp"
#include "II2CTransport.hpp"

constexpr uint32_t DELAY_TIME_MS{500};
static const char *TAG = "IMUDriver";

class StubI2CTransport : public II2CTransport
{
public:
    bool write(const uint8_t, const uint8_t, const uint8_t *, size_t) override { return true; }
    bool read(const uint8_t, const uint8_t, uint8_t *, size_t) override { return true; }
};

extern "C" void
app_main(void)
{
    imu::AccelData accelData{};
    StubI2CTransport transport;
    IMUDriver myIMU{transport};

    if (!myIMU.init())
    {
        ESP_LOGI(TAG, "Error, could not initialize imu driver");
        abort();
    }

    while (true)
    {

        accelData = myIMU.getAccel();
        ESP_LOGI(TAG, "Accel x: %.2f", accelData.x);
        ESP_LOGI(TAG, "Accel y: %.2f", accelData.y);
        ESP_LOGI(TAG, "Accel z: %.2f", accelData.z);

        vTaskDelay(pdMS_TO_TICKS(DELAY_TIME_MS));
    }
}