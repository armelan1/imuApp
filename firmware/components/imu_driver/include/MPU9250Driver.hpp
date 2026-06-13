#pragma once
#include <cstdint>
#include <cstddef>
#include "IIMUDriver.hpp"
class II2CTransport;

class MPU9250Driver : public IIMUDriver
{
public:
    MPU9250Driver(II2CTransport &transport) : _transport{transport} {}

    bool init() override;

    imu::AccelData getAccel() const override;
    imu::GyroData getGyro() const override;
    imu::MagData getMag() const override;

private:
    II2CTransport &_transport;
    static constexpr const char* TAG = "MPU9250Driver";

    static constexpr float ACCEL_2G_LSB{16384.0f};

    /* Register Map */
    static constexpr uint8_t DEV_ADDR{0x68};
    static constexpr uint8_t WHO_AM_I_ADDR{0x75};
    static constexpr uint8_t WHO_AM_I_VAL{0x73};
    static constexpr uint8_t PWR_MGMT_1{0x6B};

    /* Accelerometer Data Registers */
    static constexpr uint8_t ACCEL_XOUT_H{0x3B};
    static constexpr uint8_t ACCEL_XOUT_L{0x3C};

    static constexpr uint8_t ACCEL_YOUT_H{0x3D};
    static constexpr uint8_t ACCEL_YOUT_L{0x3E};

    static constexpr uint8_t ACCEL_ZOUT_H{0x3F};
    static constexpr uint8_t ACCEL_ZOUT_L{0x40};

    /* Private Methods */
    static int16_t parseRaw(const uint8_t* buf, size_t offset);

};
