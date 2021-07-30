#include <iostream>
#include "data.hpp"

int main() {
    std::string buf;
    auto root = get_serializable_object();

#if defined(BOOST_EXAMPLE)
    buf = serialize_boost(root);
    auto des = deserialize_boost(buf);
    std::cout << "Is serialize/deserialize result equivalent:" << is_equal(root, des) << std::endl;
    std::cout << "Is serialize/deserialize result identical :" << is_identical(root, des) << std::endl;
#elif defined(CODEGEN_EXAMPLE)
    buf = serialize_codegen(root);
    auto des = deserialize_codegen(buf);
    std::cout << "Is serialize/deserialize result equivalent:" << is_equal(root, des) << std::endl;
    std::cout << "Is serialize/deserialize result identical :" << is_identical(root, des) << std::endl;
#elif defined(PROTOBUF_EXAMPLE)
    buf = serialize_protobuf(root);
    auto des = deserialize_protobuf(buf);
    std::cout << "Is serialize/deserialize result equivalent:" << is_equal(root, des) << std::endl;
    std::cout << "Is serialize/deserialize result identical :" << is_identical(root, des) << std::endl;
#else
    buf = dump_object(root);
    std::cout << buf << std::endl;
#endif
    return 0;
}
