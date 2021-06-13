#include <iostream>
#include <sstream>
#include "bus_stop.hpp"

#ifdef BOOST_EXAMPLE
#include "bus_stop_ser.hpp"

int main() {
    bus_stop *bs1 = new bus_stop(gps(24.253475), gps(120.598994));

    std::stringstream buf;
    boost::archive::text_oarchive ar(buf);
    ar << *bs1 ;
    std::cout<< buf.str() << std::endl;

    return 0;
}
#endif

#ifdef PROTOBUF_EXAMPLE
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>

int main() {
    bus_stop *bs1 = new bus_stop(gps(24.253475), gps(120.598994));
    
    data::Gps *gps;
    data::BusStop bus_stop;
    gps = bus_stop.mutable_latitude();
    gps->set_degrees(bs1->latitude.degrees);
    gps = bus_stop.mutable_longitude();
    gps->set_degrees(bs1->longitude.degrees);
    
    std::string str;
    google::protobuf::TextFormat::PrintToString(bus_stop , &str);
    std::cout << str << std::endl;

    google::protobuf::ShutdownProtobufLibrary();

    return 0;
}
#endif