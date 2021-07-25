#include "bus_route.hpp"
#ifndef BUS_GROUP_H
#define BUS_GROUP_H
#include <vector>

/*
    bus_group is a colloection of bus_route.
*/
class bus_group
{
    friend std::ostream & operator<<(std::ostream &os, const bus_group &br);    
public:
    std::vector<bus_route*> groups;
    bus_group(std::initializer_list<bus_route*> br):groups(br){}
    bus_group(){} /* for boost serialization */
};

#endif