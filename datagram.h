#include <cstdint>
#include <fstream>

#pragma once

#define NUM_16_BIT_HEADER_FIELDS 10

class Datagram {

private:
    uint16_t totLength;
    uint8_t ttl;
    uint16_t checksum;
    
    uint16_t header[NUM_16_BIT_HEADER_FIELDS];
    char* data;


public:
    uint32_t sourceAddress;
    uint32_t destAddress;
    const char* error;
    int num;

    Datagram();

    /**
     * Destructor, delete data
     */
    ~Datagram();

    /**
     * Function to compute the checksum for the header fields
     * present in the file.
     */
    uint16_t computeChecksum();

    /**
     * Assign assign member variables in host order based on 16 bit
     * header fields.
     */
    void parseHeader();

    /** 
     * Compare the checksum that was parsed with a newly computed one.
     */
    bool compareChecksum();

    /**
     * Read a packet from a filestream.
     */
    void read(std::ifstream &input);

    /** 
     * Try to decrement the TTL value. Return false if decrementing would
     * make it 0.
     */
    bool decrementTTL();

    void setError(const char* msg);

    /**
     * Writes single packet to output stream
     */
    void write(std::ostream* output);
    
};

