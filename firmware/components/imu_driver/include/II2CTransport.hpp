#pragma once

#include <cstdint>
#include <cstddef>

class II2CTransport 
{
public:
    II2CTransport(const II2CTransport&) = delete;
    II2CTransport& operator=(const II2CTransport&) = delete;

    II2CTransport(II2CTransport&& other) = delete;
    II2CTransport& operator=(II2CTransport&& other) = delete;

    virtual ~II2CTransport() = default;

    virtual bool write(const uint8_t deviceID, const uint8_t registerAddress, const uint8_t* data, size_t size) = 0;
    virtual bool read(const uint8_t deviceID, const uint8_t registerAddress, uint8_t* data, size_t size) = 0;
    
protected:
    II2CTransport() = default;
};
