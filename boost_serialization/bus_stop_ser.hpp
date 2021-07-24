
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

    template<class Archive>
    void serialize(Archive & ar, bus_stop_detail & obj, const unsigned int version) {
        boost::serialization::base_object<bus_stop>(obj);
        ar & obj.latitude;
        ar & obj.longitude;
        ar & obj.stop_name;
    }

}
}


#endif