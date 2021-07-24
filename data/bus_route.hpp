#include "bus_stop.hpp"
#ifndef BUS_ROUTE_H
#define BUS_ROUTE_H
#include <vector>

/*
    bus_route is a colloection of bus_stop.
*/
class bus_route
{
    friend std::ostream & operator<<(std::ostream &os, const bus_route &br);    
public:
#pragma bus_stop_detail
    std::vector<bus_stop*> routes;
    bus_route(std::initializer_list<bus_stop*> br):routes(br){}
    bus_route(){} /* for boost serialization */
};

#endif