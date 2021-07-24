#include <iostream>
#include "data.hpp"
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>

extern std::string serialize_protobuf(bus_route *root) {
    data::Gps *gps;
    data::BusStop *bs;
    data::BusRoute br;
    bs = br.add_routes();
    bus_stop_detail *current = (bus_stop_detail*)root->routes[0];
    gps = bs->mutable_latitude();
    gps->set_degrees(current->latitude.degrees);
    gps = bs->mutable_longitude();
    gps->set_degrees(current->longitude.degrees);
    bs->set_stop_name(current->stop_name);
    bs = br.add_routes();
    current = (bus_stop_detail*)root->routes[1];
    gps = bs->mutable_latitude();
    gps->set_degrees(current->latitude.degrees);
    gps = bs->mutable_longitude();
    gps->set_degrees(current->longitude.degrees);
    bs->set_stop_name(current->stop_name);
    
    std::string str;
    google::protobuf::TextFormat::PrintToString(br , &str);
    
    google::protobuf::ShutdownProtobufLibrary();
    return str;
}
