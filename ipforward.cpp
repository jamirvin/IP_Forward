#include "iprouter.h"
#include "table.h"
#include <iostream>

int main(int argc, char** argv) {

    if(argc < 4) {
        std::cerr << "Usage: " << argv[0] << " <routing_table> <ip_packets> <out_file>\n";
        exit(2);
    }

    IpRouter router(argv[1], argv[2], argv[3]);

    router.getPackets();

    router.getResults();
    router.writePackets();

    return 0;
}
