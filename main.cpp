#include <iostream>
#include "data.hpp"

int main() {
    std::string buf;
    auto root = get_serializable_object();

#if defined(BOOST_EXAMPLE)
    buf = serialize_boost(root);
    auto des = deserialize_boost(buf);
    std::cout << is_equal(root, des) << std::endl;
#elif defined(CODEGEN_EXAMPLE)
    buf = serialize_codegen(root);
    std::cout << buf << std::endl;
#elif defined(PROTOBUF_EXAMPLE)
    buf = serialize_protobuf(root);
    std::cout << buf << std::endl;
#else
    buf = dump_object(root);
    std::cout << buf << std::endl;
#endif
    return 0;
}
