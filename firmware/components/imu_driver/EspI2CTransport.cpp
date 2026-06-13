#include <cstring>
#include "EspI2CTransport.hpp"

bool EspI2CTransport::init()
{
    i2c_config_t conf = {};
    conf.mode = I2C_MODE_MASTER;
    conf.sda_io_num = _sdaPin;
    conf.sda_pullup_en = GPIO_PULLUP_ENABLE;
    conf.scl_io_num = _sclPin;
    conf.scl_pullup_en = GPIO_PULLUP_ENABLE;
    conf.master.clk_speed = _clockSpeed;
    conf.clk_flags = 0;
    esp_err_t ret = i2c_param_config(_i2cPort, &conf);
    if (ret != ESP_OK)
        return false;

    ret = i2c_driver_install(_i2cPort, conf.mode, 0, 0, 0);
    return ret == ESP_OK;
}

bool EspI2CTransport::write(const uint8_t deviceID, const uint8_t registerAddress, const uint8_t *data, size_t size)
{
    uint8_t buf[size + 1];
    buf[0] = registerAddress;
    memcpy(buf + 1, data, size);
    esp_err_t ret = i2c_master_write_to_device(_i2cPort, deviceID, buf, size + 1, pdMS_TO_TICKS(1000));
    return ret == ESP_OK;
}

bool EspI2CTransport::read(const uint8_t deviceID, const uint8_t registerAddress, uint8_t* data, size_t size)
{
    esp_err_t ret = i2c_master_write_read_device(_i2cPort, deviceID, &registerAddress, 1, data, size, pdMS_TO_TICKS(1000));
    return ret == ESP_OK;
}