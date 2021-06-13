#include <iostream>
#include <sstream>
#include "data.hpp"

#ifdef BOOST_EXAMPLE
#include "bus_stop_ser.hpp"

int main() {
    bus_stop *root = get_serializable_object();

    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *root ;
    std::cout<< buf.str() << std::endl;

    return 0;
}
#endif

#ifdef PROTOBUF_EXAMPLE
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>

int main() {
    bus_stop *root = get_serializable_object();
    
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

    return 0;
}
#endif