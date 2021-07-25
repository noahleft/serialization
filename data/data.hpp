
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_group.hpp"
extern bus_group* get_serializable_object();
extern std::string serialize_boost(bus_group *root);
extern bus_group* deserialize_boost(std::string str);
extern std::string serialize_codegen(bus_group *root);
extern bus_group* deserialize_codegen(std::string str);
extern std::string serialize_protobuf(bus_group *root);
extern bus_group* deserialize_protobuf(std::string str);

extern bool is_equal(bus_group *a, bus_group *b);
extern std::string dump_object(bus_group *root);
#endif