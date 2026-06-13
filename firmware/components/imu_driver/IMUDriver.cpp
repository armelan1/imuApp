#include "IMUDriver.hpp"
#include "II2CTransport.hpp"

bool IMUDriver::init()
{
    return true;
}

imu::AccelData IMUDriver::getAccel() const
{
    imu::AccelData accelData{1.0f, 2.0f, 3.0f};
    return accelData;
}

imu::GyroData IMUDriver::getGyro() const
{
    imu::GyroData gyroData{1.0f, 2.0f, 3.0f};
    return gyroData;
}

imu::MagData IMUDriver::getMag() const
{
    imu::MagData magData{1.0f, 2.0f, 3.0f};
    return magData;
}