
#ifndef BUS_GROUP_SER_HPP
#define BUS_GROUP_SER_HPP
#include "bus_group.hpp"
#include "bus_route_ser.hpp"
#include <boost/serialization/vector.hpp>

namespace boost {
namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, bus_group & obj, const unsigned int version) {
        ar & obj.groups;
    }
}
}


#endif