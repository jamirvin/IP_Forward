#include "iprouter.h"


int main() {

    IpRouter reader("ip_packets");

    reader.getPackets();

    return 0;
}
