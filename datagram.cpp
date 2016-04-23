#include "datagram.h"
#include <arpa/inet.h>
#include <iostream>
#include <fstream>

/**
 * Implementation of Datagram methods. 
 * 
 * For each method's description see header file datagram.
 */

Datagram::Datagram() {
    num = 0;
    error = NULL;
}

Datagram::~Datagram() {
    delete[] data;
}

uint16_t Datagram::computeChecksum() {
    uint32_t tot = 0;

    // Add the bits, subtracting by 0xffff if it goes over 16 bits
    for(int i = 0; i < NUM_16_BIT_HEADER_FIELDS; i++) {
        tot += ntohs(header[i]);
        if(tot > 0xffff) 
            tot -= 0xffff;
    }

    return htons(~tot);
}

bool Datagram::compareChecksum() {
    return checksum == computeChecksum();
}

void Datagram::read(std::ifstream &input) {
    // Read in every 16 bits into its own array. These header arrays
    // are kept in Network Byte Order
    for(int i = 0; i < NUM_16_BIT_HEADER_FIELDS; i++) {
        input.read(reinterpret_cast<char*>(&header[i]), 2);
    }

    // Parse the arrays
    parseHeader();

    // Read the packet data
    data = new char[totLength - 20];
    input.read(data, totLength - 20);
}

void Datagram::parseHeader() {
    totLength = ntohs(header[1]);
    ttl = header[4] & 0x00ff;
    checksum = header[5];
    header[5] = 0;
    sourceAddress = ntohl( (uint32_t)header[6] + ((uint32_t)header[7] << 16) );
    destAddress = ntohl( (uint32_t)header[8] + ((uint32_t)header[9] << 16) );
}

bool Datagram::decrementTTL() {
    // If the TTL becomes 0 return false
    if (ttl <= 1) 
        return false;

    // Otherwise decrement TTL and set header array
    uint16_t newTTL = --ttl;
    header[4] = (header[4] & 0xff00) + newTTL;

    return true;
}

void Datagram::setError(const char* msg) {
    // Set packet error message
    error = msg;
}

void Datagram::write(std::ostream* output) {
    // Compute the checksum and store it in header array before writing 
    // to output stream
    header[5] = computeChecksum();

    // Output each header field to stream
    for( int i = 0; i < 10; ++i) {
        output->write( (char*)header + i, sizeof(uint16_t));
    }

    // Write data
    output->write( data, totLength - 20);
}
