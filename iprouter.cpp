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
            
    // Open the packet file
    packetsFS.open(packetsFile, std::ios::binary);
}

IpRouter::~IpRouter() {
    // Delete each dynamically allocated packet.
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

    // Create a packet on the Heap so it can exist longer than the scope of this function
    Datagram* packet = new Datagram;

    // Read packet data into object
    packet->read(packetsFS);

    return packet;
}

void IpRouter::outputError(Datagram packet, std::string error) {
    std::cout << "Packet Dropped: " << error << std::endl;
}

void IpRouter::getPackets() {
    Datagram* packet;
    int counter = 1;
    // Read in every packet until the end of the file
    while((packet = readPacket())) {

        // Check for checksum and TTL errors
        if( !packet->compareChecksum() ) {
            packet->setError("Checksum is incorrect");
        } else if( !packet->decrementTTL()) {
            packet->setError("TTL becomes 0");
        } 

        // Set packet number
        packet->num = counter;

        // Store packet in vector
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

        // Check if there was an error. If no error, get next hop address
        if (it->error) {
            outcome = "Packet Dropped: ";
            outcome += it->error;
        } else {
            outcome = "Packet forwarded to ";
            outcome += RoutingTable::addr_htos(table.getNextHop(it->destAddress));
        }

        // Convert Addresses to strings
        std::string source = RoutingTable::addr_htos(it->sourceAddress);
        std::string dest = RoutingTable::addr_htos(it->destAddress);

        // Output formatted string
        printf("%d\t%s\t%s\t%s\n", it->num, source.c_str(), dest.c_str(), outcome.c_str());
    }
}

void IpRouter::writePackets() {
    // Create output filestream
    std::ofstream out(outFile, std::ofstream::binary);

    // If there is no error, write packet to output file
    for(auto it : datagrams) {
        if (it->error == NULL)
            it->write(&out);
    }

    out.close();
}

