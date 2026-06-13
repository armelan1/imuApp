#pragma once
#include "driver/gpio.h"
#include "driver/i2c.h"
#include "II2CTransport.hpp"

class EspI2CTransport : public II2CTransport
{
public:
    EspI2CTransport(gpio_num_t sdaPin,
                    gpio_num_t sclPin,
                    uint32_t clockSpeed,
                    i2c_port_t i2cPort) : _sdaPin(sdaPin),
                                          _sclPin(sclPin),
                                          _clockSpeed(clockSpeed),
                                          _i2cPort(i2cPort) {}

    bool init();
    bool write(const uint8_t, const uint8_t, const uint8_t *, size_t) override;
    bool read(const uint8_t, const uint8_t, uint8_t *, size_t) override;

private:
    gpio_num_t _sdaPin;
    gpio_num_t _sclPin;
    uint32_t _clockSpeed;
    i2c_port_t _i2cPort;
};
