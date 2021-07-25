#include <sstream>
#include "data.hpp"
#include "bus_group_ser.hpp"

extern std::string serialize_boost(bus_group *root) {
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    return buf.str();
}

extern bus_group* deserialize_boost(std::string str) {
    std::stringstream buf;
    buf << str;
    boost::archive::text_iarchive ar(buf);
    bus_group *root = new bus_group();
    ar >> *root;
    return root;
}
