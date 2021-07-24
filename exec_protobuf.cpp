#include <iostream>
#include "data.hpp"
#include "addressbook.pb.h"
#include <google/protobuf/text_format.h>

// adaptor: translate bus stop data to protobuf required model
static void translate_bus_stop(data::BusStop *model_bus_stop, bus_stop_detail *data) {
    data::Gps *gps;
    gps = model_bus_stop->mutable_latitude();
    gps->set_degrees(data->latitude.degrees);
    gps = model_bus_stop->mutable_longitude();
    gps->set_degrees(data->longitude.degrees);
    model_bus_stop->set_stop_name(data->stop_name);
}

// adaptor: translate bus route data to protobuf required model
static void translate_bus_route(data::BusRoute *model, bus_route *data) {
    data::Gps *gps;
    data::BusStop *model_bus_stop;
    for(unsigned int i=0; i<data->routes.size(); i++) {
        model_bus_stop = model->add_routes();
        bus_stop_detail *current = (bus_stop_detail*)data->routes[i];
        translate_bus_stop(model_bus_stop, current);
    }
}

extern std::string serialize_protobuf(bus_route *root) {
    data::BusRoute model;
    translate_bus_route(&model, root);
    
    std::string str;
    google::protobuf::TextFormat::PrintToString(model , &str);
    
    google::protobuf::ShutdownProtobufLibrary();
    return str;
}
