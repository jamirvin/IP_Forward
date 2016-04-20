#include <cstdint>

#pragma once

typedef struct {
    uint16_t totLength;
    uint8_t ttl;
    uint16_t checksum;
    uint32_t sourceAddress;
    uint32_t destAddress;
} Datagram;

