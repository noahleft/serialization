#include <iostream>
#include <sstream>
#include "data.hpp"

extern bus_route* get_serializable_object() {
    bus_stop * bs1 = new bus_stop(gps(24.253475), gps(120.598994)); // Taichung Airport
    bus_stop * bs2 = new bus_stop(gps(24.1086998), gps(120.6144028)); //Xinwuri Station
    bus_route *br1 = new bus_route{bs1, bs2};
    return br1;
}

extern std::string dump_object(bus_route *root) {
    std::stringstream buf;
    buf << *root ;
    return buf.str();
}

std::ostream & operator<<(std::ostream &os, const gps &gp){
    return os << gp.degrees;
}

std::ostream & operator<<(std::ostream &os, const bus_stop &bs) {
    return os << "lat:" << bs.latitude << " lng:" << bs.longitude;
}

 std::ostream & operator<<(std::ostream &os, const bus_route &br) {
    for (auto itr=br.routes.begin(); itr!=br.routes.end(); itr++) {
        os << **itr << std::endl;
    }
    return os;
}