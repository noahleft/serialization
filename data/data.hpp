
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_route.hpp"
extern bus_route* get_serializable_object();
extern std::string serialize_boost(bus_route *root);
extern bus_route* deserialize_boost(std::string str);
extern std::string serialize_codegen(bus_route *root);
extern bus_route* deserialize_codegen(std::string str);
extern std::string serialize_protobuf(bus_route *root);
extern bus_route* deserialize_protobuf(std::string str);

extern bool is_equal(bus_route *a, bus_route *b);
extern std::string dump_object(bus_route *root);
#endif