#include "iprouter.h"


int main() {

    IpRouter reader("ip_packets");

    reader.readPacket();

    return 0;
}
