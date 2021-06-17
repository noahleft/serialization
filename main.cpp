#include <iostream>
#include <sstream>
#include "data.hpp"

#if defined(BOOST_EXAMPLE)
#include "bus_route_ser.hpp"
#elif defined(PROTOBUF_EXAMPLE)
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>
#endif

int main() {
    bus_route *root = get_serializable_object();

#if defined(BOOST_EXAMPLE)
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    std::cout<< buf.str() << std::endl;
#elif defined(PROTOBUF_EXAMPLE)
    data::Gps *gps;
    data::BusStop *bs;
    data::BusRoute br;
    bs = br.add_routes();
    bus_stop *current = root->routes[0];
    gps = bs->mutable_latitude();
    gps->set_degrees(current->latitude.degrees);
    gps = bs->mutable_longitude();
    gps->set_degrees(current->longitude.degrees);
    bs = br.add_routes();
    current = root->routes[1];
    gps = bs->mutable_latitude();
    gps->set_degrees(current->latitude.degrees);
    gps = bs->mutable_longitude();
    gps->set_degrees(current->longitude.degrees);
    
    std::string str;
    google::protobuf::TextFormat::PrintToString(br , &str);
    std::cout << str << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
#else
    std::cout << *root << std::endl;
#endif

    return 0;
}
