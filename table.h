#include <fstream>
#include <cstdint>
#include <vector>
#include <string>

#pragma once

/**
 * Structure for keeping the data from each row of the routing table.
 */
typedef struct {
    uint32_t netid;
    uint32_t netmask;
    uint32_t nextHop;
} Route;

class RoutingTable {

private:
    // Properties
    const char* tableFile;
    std::vector<Route> routes;

public:

    /**
     * Construct the object by taking in the filename 
     * and assigning it to that property.
     */
    RoutingTable(const char* filename);

    /**
     * Convert string representation of IP Address to int.
     * Static because it doesn't rely on any object data and 
     * so it can be used without needing an instance of this class.
     */
    static uint32_t addr_stoh(std::string ipString);

    /**
     * Convert int representation of IP Address to string.
     */
    static const char* addr_htos(uint32_t ipInt);

    /**
     * Read in the forwarding table.
     */
    void read();

    /**
     * Get the next hop given the forwarding table
     * already read
     */
    uint32_t getNextHop(uint32_t destination);

};
