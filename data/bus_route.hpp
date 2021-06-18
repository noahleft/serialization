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
    std::vector<bus_stop*> routes;
    bus_route(std::initializer_list<bus_stop*> br):routes(br){}
};

#endif