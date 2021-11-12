#include <sstream>
#include "data.hpp"
#include "data_ser.hpp"

extern std::string serialize(ROOT_TYPE *root) {
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    return buf.str();
}

extern ROOT_TYPE* deserialize(std::string str) {
    std::stringstream buf;
    buf << str;
    boost::archive::text_iarchive ar(buf);
    ROOT_TYPE *root = new ROOT_TYPE();
    ar >> *root;
    return root;
}

