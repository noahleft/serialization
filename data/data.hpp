
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_stop.hpp"

static inline bus_stop* get_serializable_object() {
    bus_stop * bs1 = new bus_stop(gps(24.253475), gps(120.598994));
    return bs1;
}

#endif