#include "iprouter.h"
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

IpRouter::IpRouter(std::string packetsFile) {
    packetsFilename = packetsFile;

    packetsFS.open(packetsFile.c_str(), std::ios::binary);
}

Datagram IpRouter::readPacket() {
    Datagram packet;
    packetsFS.read(NULL, 16);
    packetsFS.read((char*)&packet.totLength, 16);

    std::cout << packet.totLength;


    packetsFS.close();

    return packet;
}

