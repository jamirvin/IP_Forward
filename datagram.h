#include <cstdint>

#pragma once

class Datagram {

public:
    uint16_t totLength;
    uint8_t ttl;
    uint16_t checksum;
    uint32_t sourceAddress;
    uint32_t destAddress;

    uint16_t computeChecksum();
    
};

