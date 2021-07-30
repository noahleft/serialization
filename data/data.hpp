
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_group.hpp"
#define ROOT_TYPE bus_group
extern ROOT_TYPE* get_serializable_object();
extern std::string serialize_boost(ROOT_TYPE *root);
extern ROOT_TYPE* deserialize_boost(std::string str);
extern std::string serialize_codegen(ROOT_TYPE *root);
extern ROOT_TYPE* deserialize_codegen(std::string str);
extern std::string serialize_protobuf(ROOT_TYPE *root);
extern ROOT_TYPE* deserialize_protobuf(std::string str);

extern bool is_equal(ROOT_TYPE *a, ROOT_TYPE *b);
extern bool is_identical(ROOT_TYPE *a, ROOT_TYPE *b);
extern std::string dump_object(ROOT_TYPE *root);
#endif