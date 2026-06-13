#pragma once

namespace imu
{
    struct AccelData
    {
        float x;
        float y;
        float z;
    };

    struct GyroData
    {
        float x;
        float y;
        float z;
    };

    struct MagData
    {
        float x;
        float y;
        float z;
    };
} // namespace imu

class IIMUDriver
{
public:
    IIMUDriver(const IIMUDriver&) = delete;
    IIMUDriver& operator=(const IIMUDriver&) = delete;

    IIMUDriver(IIMUDriver&& other) = delete;
    IIMUDriver& operator=(IIMUDriver&& other) = delete;

    virtual ~IIMUDriver() = default;

    virtual bool init() = 0;

    virtual imu::AccelData getAccel() const = 0;
    virtual imu::GyroData getGyro() const = 0;
    virtual imu::MagData getMag() const = 0;
    
protected:
    IIMUDriver() = default;
};