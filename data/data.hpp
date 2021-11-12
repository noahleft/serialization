
#ifndef DATA_HPP
#define DATA_HPP
#include "bus_group.hpp"
#define ROOT_TYPE bus_group
extern ROOT_TYPE* get_serializable_object();
/* Universal API to serialize data*/
extern std::string serialize(ROOT_TYPE *root);
extern ROOT_TYPE* deserialize(std::string str);
/* Checker */
extern bool is_equal(ROOT_TYPE *a, ROOT_TYPE *b);
extern bool is_identical(ROOT_TYPE *a, ROOT_TYPE *b);
extern std::string dump_object(ROOT_TYPE *root);
#endif