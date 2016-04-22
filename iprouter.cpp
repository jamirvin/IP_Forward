#include "iprouter.h"
#include "table.h"
#include <string>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <arpa/inet.h>
#include <stdio.h>

IpRouter::IpRouter(const char* routingFile,
                   const char* packetsFile,
                   const char* outFile) : 
                   packetsFile(packetsFile), 
                   outFile(outFile), 
                   routingFile(routingFile)
{
            
    packetsFS.open(packetsFile, std::ios::binary);
}

IpRouter::~IpRouter() {
    for (auto it : datagrams) {
        delete it;
    }
}

Datagram* IpRouter::readPacket() {
    // If the file stream is at the end of the file, all packets have been read. Return NULL.
    if(packetsFS.peek() == EOF) {
        packetsFS.close();
        return NULL;
    }

    Datagram* packet = new Datagram;

    packet->read(packetsFS);

    return packet;
}

void IpRouter::outputError(Datagram packet, std::string error) {
    std::cout << "Packet Dropped: " << error << std::endl;
}

void IpRouter::getPackets() {
    Datagram* packet;
    int counter = 1;
    while((packet = readPacket())) {

        if( !packet->compareChecksum() ) {
            packet->setError("Checksum is incorrect");
        } else if( !packet->decrementTTL()) {
            packet->setError("TTL becomes 0");
        } 

        packet->num = counter;

        datagrams.push_back(packet);
        ++counter;
    }
}

void IpRouter::getResults() {
    
    RoutingTable table(routingFile);
    table.read();

    printf("Packet#\tSource\t\tDestination\tOutcome\n");
    for( auto it : datagrams) {
        std::string outcome;

        if (it->error) {
            outcome = "Packet Dropped: ";
            outcome += it->error;
        } else {
            outcome = "Packet forwarded to ";
            outcome += RoutingTable::addr_htos(table.getNextHop(it->destAddress));
        }

        std::string source = RoutingTable::addr_htos(htonl(it->sourceAddress));
        std::string  dest = RoutingTable::addr_htos(it->destAddress);

        printf("%d\t%s\t%s\t%s\n", it->num, source.c_str(), dest.c_str(), outcome.c_str());
    }
}

void IpRouter::writePackets() {
    std::ofstream out(outFile, std::ofstream::binary);

    for(auto it : datagrams) {
        if (it->error == NULL)
            it->write(&out);
    }

    out.close();
}

