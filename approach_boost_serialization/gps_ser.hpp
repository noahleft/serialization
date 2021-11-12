#include "gps.hpp"
#ifndef GPS_SER_HPP
#define GPS_SER_HPP

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

namespace boost {
namespace serialization {

    template<class Archive>
    void serialize(Archive & ar, gps & g, const unsigned int version) {
        ar & g.degrees;
    }
}
}


#endif