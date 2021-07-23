#include <iostream>
#include "data.hpp"

int main() {
    std::string buf;
    auto root = get_serializable_object();

#if defined(BOOST_EXAMPLE)
    buf = serialize_boost(root);
#elif defined(CODEGEN_EXAMPLE)
    buf = serialize_codegen(root);
#elif defined(PROTOBUF_EXAMPLE)
    buf = serialize_protobuf(root);
#else
    buf = dump_object(root);
#endif
    std::cout << buf << std::endl;
    return 0;
}
