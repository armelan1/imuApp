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
    imu::AccelData accelData{};
    constexpr size_t SIZE{6};
    uint8_t buffer[SIZE];
    if(!_transport.read(DEV_ADDR, ACCEL_XOUT_H, buffer, SIZE))
    {
        ESP_LOGI(TAG, "Error, could not read accelerometer data");
        return accelData;
    }
    accelData.x = parseRaw(buffer, 0) / ACCEL_2G_LSB;
    accelData.y = parseRaw(buffer, 2) / ACCEL_2G_LSB;
    accelData.z = parseRaw(buffer, 4) / ACCEL_2G_LSB;

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

int16_t MPU9250Driver::parseRaw(const uint8_t* buf, size_t offset)
{
    return (int16_t)((buf[offset] << 8) | buf[offset + 1]);
}