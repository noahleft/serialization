#include <iostream>
#include "bus_stop.hpp"
#include "gps_ser.hpp"
#include <sstream>

int main() {
    bus_stop *bs1 = new bus_stop(gps(24.253475), gps(120.598994));

    std::stringstream buf;
    buf << bs1->latitude ;
    std::cout<< buf.str() << std::endl;

    return 0;
}