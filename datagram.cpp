#include "datagram.h"
#include <arpa/inet.h>
#include <iostream>
#include <fstream>

uint16_t Datagram::computeChecksum() {
    uint32_t tot = 0;

    for(int i = 0; i < NUM_16_BIT_HEADER_FIELDS; i++) {
        tot += ntohs(header[i]);
        if(tot > 0xffff) 
            tot -= 0xffff;
    }

    std::cout << std::hex << htons(~tot) << std::dec << std::endl;
    return htons(~tot);
}

bool Datagram::compareChecksum() {
    return checksum == computeChecksum();
}

void Datagram::readHeader(std::ifstream &input) {
    for(int i = 0; i < NUM_16_BIT_HEADER_FIELDS; i++) {
        input.read(reinterpret_cast<char*>(&header[i]), 2);
    }

    parseHeader();
}

void Datagram::parseHeader() {
    totLength = ntohs(header[1]);
    ttl = header[4] & 0x00ff;
    checksum = header[5];
    header[5] = 0;
    sourceAddress = ntohl( (uint32_t)header[6] + ((uint32_t)header[7] << 16) );
    destAddress = ntohl( (uint32_t)header[8] + ((uint32_t)header[8] << 16) );
}
