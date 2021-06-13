#include <iostream>
#include "bus_stop.hpp"

int main() {
    bus_stop *bs1 = new bus_stop(gps(24.253475), gps(120.598994));

    std::cout<< *bs1 <<std::endl;
    return 0;
}