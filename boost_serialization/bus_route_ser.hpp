
#ifndef BUS_ROUTE_SER_HPP
#define BUS_ROUTE_SER_HPP
#include "bus_route.hpp"
#include "bus_stop_ser.hpp"
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, bus_route & obj, const unsigned int version) {
        ar & obj.routes;
    }
}
}


#endif