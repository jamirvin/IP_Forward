## Description:

Simple project to learn about IP Routing. Read packets from a file
in Network Byte Order and use a IP Forwarding Table also provided
to output the next hop address for each packet. Updates the TTL and
checksum values for the packets and outputs those that are valid
to an output file.

## Build instructions:

Use the included makefile with the default target.

`$ make`

Usage: `./ipforward <Forwarding table> <ip packets> <output file>`


Everything seems to work pretty well according to the requirements.
Once possible shortcoming is that because I read in and store the
entire packets file at a time it could fail for exceptionally large
packet files. If I needed to handle those or this was reading from 
a socket I would reorganize to have it handle each packet as it is 
read.
