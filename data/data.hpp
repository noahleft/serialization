
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_route.hpp"
extern bus_route* get_serializable_object();
extern std::string serialize_boost(bus_route *root);
extern std::string serialize_codegen(bus_route *root);
extern std::string serialize_protobuf(bus_route *root);
extern std::string dump_object(bus_route *root);
#endif