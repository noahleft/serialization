#include <sstream>
#include "data.hpp"
#include "bus_route_ser.hpp"

extern std::string serialize_boost(bus_route *root) {
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    return buf.str();
}
