#pragma once

class II2CTransport;

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

class IMUDriver
{
public:
    IMUDriver(II2CTransport& transport) : _transport{transport} {}

    bool init();

    imu::AccelData getAccel() const;
    imu::GyroData getGyro() const;
    imu::MagData getMag() const;

private:
    II2CTransport& _transport;
};

