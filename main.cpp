#include <iostream>
#include <sstream>
#include "data.hpp"

#if defined(BOOST_EXAMPLE)
#include "bus_stop_ser.hpp"
#elif defined(PROTOBUF_EXAMPLE)
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>
#endif

int main() {
    bus_stop *root = get_serializable_object();

#if defined(BOOST_EXAMPLE)
    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    std::cout<< buf.str() << std::endl;
#elif defined(PROTOBUF_EXAMPLE)
    data::Gps *gps;
    data::BusStop bus_stop;
    gps = bus_stop.mutable_latitude();
    gps->set_degrees(root->latitude.degrees);
    gps = bus_stop.mutable_longitude();
    gps->set_degrees(root->longitude.degrees);
    
    std::string str;
    google::protobuf::TextFormat::PrintToString(bus_stop , &str);
    std::cout << str << std::endl;

    google::protobuf::ShutdownProtobufLibrary();
#endif

    return 0;
}
