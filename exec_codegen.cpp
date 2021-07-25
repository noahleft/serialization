#include <sstream>
#include "data.hpp"
#include "data_ser.hpp"

extern std::string serialize_codegen(bus_route *root) {
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    return buf.str();
}

extern bus_route* deserialize_codegen(std::string str) {
    std::stringstream buf;
    buf << str;
    boost::archive::text_iarchive ar(buf);
    bus_route *root = new bus_route();
    ar >> *root;
    return root;
}

