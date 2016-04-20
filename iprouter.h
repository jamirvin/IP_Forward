#include "datagram.h"
#include <vector>
#include <string>
#include <fstream>

#pragma once

class IpRouter {
    
private:
    std::vector<Datagram> datagrams;
    std::string packetsFilename;
    std::string outFilename;
    std::string forwardingTableFilename;

    std::ifstream packetsFS;


public: 
    /**
     * Takes the names of the files used and stores them in the 
     * object opening filestreams when appropriate.
     */
    IpRouter(std::string packetsFile);

    /**
     * Reads packets from the packets file and returns a Datagram 
     * struct with the data fields assigned.
     */
    Datagram readPacket();
};


