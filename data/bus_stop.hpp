#include "gps.hpp"
#ifndef BUS_STOP_H
#define BUS_STOP_H

class bus_stop
{
    friend std::ostream & operator<<(std::ostream &os, const bus_stop &gp);
    /* each bus stop contains the position info */
    
public:
    gps latitude;
    gps longitude;
    bus_stop(gps lat, gps lng):latitude(lat),longitude(lng){}
};

std::ostream & operator<<(std::ostream &os, const bus_stop &bs) {
    return os << "lat:" << bs.latitude << " lng:" << bs.longitude;
}


#endif