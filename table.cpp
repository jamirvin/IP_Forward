#include "table.h"
#include <fstream>
#include <string>
#include <arpa/inet.h>
#include <algorithm>
#include <iostream>

RoutingTable::RoutingTable(const char* filename) : tableFile(filename) {}

uint32_t RoutingTable::addr_stoh(std::string ipString) {
    struct sockaddr_in sa;
    inet_pton(AF_INET, ipString.c_str(), &(sa.sin_addr));

    return ntohl(sa.sin_addr.s_addr);
}

const char* RoutingTable::addr_htos(uint32_t ipInt) {
    char str[INET_ADDRSTRLEN];
    struct sockaddr_in sa;

    sa.sin_addr.s_addr = htonl(ipInt);
    inet_ntop(AF_INET, &(sa.sin_addr), str, INET_ADDRSTRLEN);

    std::string output = str;
    return output.c_str();
}

void RoutingTable::read() {
    std::ifstream infile(tableFile, std::ios::in);
    std::string sNetid, sNetmask, sNextHop;
    
    // Get the IP Addresses from each row and store them in vector
    while(infile >> sNetid >> sNetmask >> sNextHop) {
        Route route;

        route.netid = addr_stoh(sNetid);
        route.netmask = addr_stoh(sNetmask);
        route.nextHop = addr_stoh(sNextHop);

        routes.push_back(route);
    }

    // Sort the vector so longer netids occur before smaller. Used 
    // for longest pattern matching
    std::sort(routes.begin(), routes.end(), [] (Route a, Route b) { 
        return a.netmask > b.netmask; 
    } );

    infile.close();
}

uint32_t RoutingTable::getNextHop(uint32_t destination) {
    for( auto it : routes) {
        if( (it.netmask & destination) == it.netid ) {
            return it.nextHop;
        }
    }

    std::cout << "Error: Routing table does not have a case for this destination - " 
        << destination << std::endl;
    exit(1);

    return -1;
}
