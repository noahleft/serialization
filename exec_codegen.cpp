#include <sstream>
#include "data.hpp"
#include "data_ser.hpp"

extern std::string serialize_codegen(bus_route *root) {
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    return buf.str();
}