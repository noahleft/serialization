#include <iostream>
#include "data.hpp"

int main() {
    std::string buf;
    auto root = get_serializable_object();

#if defined(SERIALIZE)
    buf = serialize(root);
    auto des = deserialize(buf);
    std::cout << "Is serialize/deserialize result equivalent:" << is_equal(root, des) << std::endl;
    std::cout << "Is serialize/deserialize result identical :" << is_identical(root, des) << std::endl;
#else
    buf = dump_object(root);
    std::cout << buf << std::endl;
#endif
    return 0;
}
