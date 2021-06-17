
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_route.hpp"

static inline bus_route* get_serializable_object() {
    bus_stop * bs1 = new bus_stop(gps(24.253475), gps(120.598994)); // Taichung Airport
    bus_stop * bs2 = new bus_stop(gps(24.1086998), gps(120.6144028)); //Xinwuri Station
    bus_route *br1 = new bus_route{bs1, bs2};
    return br1;
}

#endif