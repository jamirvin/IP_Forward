#include "datagram.h"
#include <vector>
#include <string>
#include <fstream>

#pragma once

class IpRouter {
    
private:
    std::vector<Datagram*> datagrams;

    const char* packetsFile;
    const char* outFile;
    const char* routingFile;

    std::ifstream packetsFS;


public: 
    /**
     * Takes the names of the files used and stores them in the 
     * object opening filestreams when appropriate.
     */
    IpRouter(const char*  packetsFile, const char* routingFile, const char* outFile);

    /**
     * Destructor, deallocate packets
     */
    ~IpRouter();

    /**
     * Reads the next packet from the packets file and returns a Datagram 
     * struct with the data fields assigned.
     */
    Datagram* readPacket();

    /**
     * Gets all packets, checks for if they are valid, and stores the
     * valid ones in the datagrams vector.
     */
    void getPackets();

    /**
     * Output error message that packet has been dropped for reason given.
     */
    void outputError(Datagram packet, std::string error);

    /**
     * Output the results of the ip routing to the terminal.
     */
    void getResults();

    /**
     * Writes packets to file
     */
    void writePackets();
};


