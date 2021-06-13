
#ifndef BUS_STOP_SER_HPP
#define BUS_STOP_SER_HPP
#include "bus_stop.hpp"
#include "gps_ser.hpp"

namespace boost {
namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, bus_stop & obj, const unsigned int version) {
        ar & obj.latitude;
        ar & obj.longitude;
    }
}
}


#endif