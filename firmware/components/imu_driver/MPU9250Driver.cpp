#include "MPU9250Driver.hpp"
#include "II2CTransport.hpp"
#include "esp_log.h"

bool MPU9250Driver::init()
{
    constexpr size_t SIZE{1};
    uint8_t data[SIZE];
    if(!_transport.read(DEV_ADDR, WHO_AM_I_ADDR, data, SIZE))
    {
        ESP_LOGI(TAG, "Error, could not read imu id register");
        return false;
    }

    if(WHO_AM_I_VAL != *data)
    {
        ESP_LOGI(TAG, "Error, device id is incorrect");
        return false;
    }
    
    data[0] = 0x00;
    return _transport.write(DEV_ADDR, PWR_MGMT_1, data, SIZE);
}

imu::AccelData MPU9250Driver::getAccel() const
{
    imu::AccelData accelData{1.0f, 2.0f, 3.0f};
    return accelData;
}

imu::GyroData MPU9250Driver::getGyro() const
{
    imu::GyroData gyroData{1.0f, 2.0f, 3.0f};
    return gyroData;
}

imu::MagData MPU9250Driver::getMag() const
{
    imu::MagData magData{1.0f, 2.0f, 3.0f};
    return magData;
}