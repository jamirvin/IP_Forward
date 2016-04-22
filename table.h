#include <fstream>
#include <cstdint>
#include <vector>
#include <string>

#pragma once

typedef struct {
    uint32_t netid;
    uint32_t netmask;
    uint32_t nextHop;
} Route;

class RoutingTable {

private:
    const char* tableFile;
    std::vector<Route> routes;

public:

    RoutingTable(const char* filename);

    static uint32_t addr_stoh(std::string ipString);

    static const char* addr_htos(uint32_t ipInt);

    void read();

    uint32_t getNextHop(uint32_t destination);

};
