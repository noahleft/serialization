#include "gps.hpp"
#ifndef BUS_STOP_H
#define BUS_STOP_H

class bus_stop
{
    friend std::ostream & operator<<(std::ostream &os, const bus_stop &bs);
public:
    gps latitude;
    gps longitude;
    bus_stop(gps lat, gps lng):latitude(lat),longitude(lng){}
};

class bus_stop_detail: public bus_stop
{
public:
    std::string stop_name;
    bus_stop_detail(std::string stop_name, gps lat, gps lng):bus_stop(lat, lng), stop_name(stop_name){}
};

#endif