#include "iprouter.h"
#include "table.h"

int main() {

    IpRouter router("test_files/routing_table.txt", "test_files/ip_packets", "");

    router.getPackets();

    router.getResults();

    return 0;
}
