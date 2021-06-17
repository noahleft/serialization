#include "bus_stop.hpp"
#ifndef BUS_ROUTE_H
#define BUS_ROUTE_H
#include <vector>

class bus_route
{
    friend std::ostream & operator<<(std::ostream &os, const bus_stop &gp);
    
public:
    std::vector<bus_stop*> routes;
    bus_route(std::initializer_list<bus_stop*> br):routes(br){}
};

std::ostream & operator<<(std::ostream &os, const bus_route &br) {
    for (auto itr=br.routes.begin(); itr!=br.routes.end(); itr++) {
        os << **itr << std::endl;
    }
    return os;
}


#endif