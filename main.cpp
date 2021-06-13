#include <iostream>
#include "bus_stop.hpp"
#include "bus_stop_ser.hpp"
#include <sstream>

int main() {
    bus_stop *bs1 = new bus_stop(gps(24.253475), gps(120.598994));

    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *bs1 ;
    std::cout<< buf.str() << std::endl;

    return 0;
}