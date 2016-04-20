#include "iprouter.h"
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>

IpRouter::IpRouter(std::string packetsFile) {
    packetsFilename = packetsFile;

    packetsFS.open(packetsFile.c_str(), std::ios::binary);
}

Datagram* IpRouter::readPacket() {
    // If the file stream is at the end of the file, all packets have been read. Return NULL.
    if(packetsFS.peek() == EOF) {
        packetsFS.close();
        return NULL;
    }

    static Datagram packet;

    uint16_t twoBytes = 0;
    uint32_t fourBytes = 0;

    // Read in the datagram length, convert it to host order and store it in the struct.
    packetsFS.seekg(2, std::ios::cur);
    packetsFS.read(reinterpret_cast<char*>(&twoBytes), 2);
    packet.totLength = ntohs(twoBytes);

    // Read in the ttl
    packetsFS.seekg(4, std::ios::cur);
    packetsFS.read(reinterpret_cast<char*>(&packet.ttl), 1);

    // Read in the checksum
    packetsFS.seekg(1, std::ios::cur);
    packetsFS.read(reinterpret_cast<char*>(&twoBytes), 2);
    packet.checksum = ntohs(twoBytes);

    // Read the source address
    packetsFS.read(reinterpret_cast<char*>(&fourBytes), 4);
    packet.sourceAddress = ntohl(fourBytes);

    // Read the destination address
    packetsFS.read(reinterpret_cast<char*>(&fourBytes), 4);
    packet.destAddress = ntohl(fourBytes);

    // Move file pointer to end of packet
    packetsFS.seekg(packet.totLength - 20, std::ios::cur);

    std::cout << packet.totLength << std::endl;
    std::cout << unsigned(packet.ttl) << std::endl;
    std::cout << std::hex << packet.checksum << std::endl;
    std::cout << std::dec << packet.sourceAddress  << std::endl;
    std::cout << packet.destAddress  << std::endl;
    
    return &packet;
}

void IpRouter::getPackets() {
    Datagram* packet;
    while((packet = readPacket())) {
        ;
    }

}

