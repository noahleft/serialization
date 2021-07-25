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
    model.SerializeToString(&str);
    
    google::protobuf::ShutdownProtobufLibrary();
    return str;
}

// adaptor: translate back the protobuf model to bus stop data
static bus_stop_detail* restore_bus_stop(data::BusStop *model) {
    bus_stop_detail* data = new bus_stop_detail();
    data::Gps gps;
    gps = model->latitude();
    data->latitude.degrees = gps.degrees();
    gps = model->longitude();
    data->longitude.degrees = gps.degrees();
    data->stop_name = model->stop_name();
    return data;
}

// adaptor: translate back the protobuf model to bus route data
static bus_route* restore_bus_route(data::BusRoute *model) {
    bus_route* data = new bus_route();
    for(unsigned i=0; i<model->routes_size(); i++) {
        auto model_bus_stop = model->routes(i);
        bus_stop_detail* bstop = restore_bus_stop(&model_bus_stop);
        data->routes.push_back(bstop);
    }
    return data;
}

extern bus_route* deserialize_protobuf(std::string str) {
    data::BusRoute model;
    model.ParseFromString(str);

    bus_route* root = restore_bus_route(&model);

    google::protobuf::ShutdownProtobufLibrary();
    return root;
}