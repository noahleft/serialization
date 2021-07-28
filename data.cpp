#include <iostream>
#include <sstream>
#include "data.hpp"

extern ROOT_TYPE* get_serializable_object() {
    bus_stop_detail * bs281_1 = new bus_stop_detail("Gancheng Station", gps(24.14092667), gps(120.686055));
    bus_stop_detail * bs281_2 = new bus_stop_detail("Taichung Railway Station", gps(24.13790333), gps(120.685305));
    bus_stop_detail * bs281_3 = new bus_stop_detail("Taichung Winery (Fuxing Rd.)", gps(24.13408462), gps(120.6821537));
    bus_stop_detail * bs281_4 = new bus_stop_detail("Cultural Creativity Park", gps(24.133169), gps(120.67994));
    bus_stop_detail * bs281_5 = new bus_stop_detail("Linzucuo", gps(24.13187833), gps(120.6770733));
    bus_stop_detail * bs281_6 = new bus_stop_detail("Fuxing-Youheng Intersection", gps(24.13144333), gps(120.67581));
    bus_route *br281 = new bus_route("r281", {bs281_1,bs281_2,bs281_3,bs281_4,bs281_5,bs281_6});
    bus_stop_detail * bs284_1 = new bus_stop_detail("Taichung Railway Station", gps(24.136313), gps(120.68301));
    bus_stop_detail * bs284_2 = new bus_stop_detail("The Third Market", gps(24.133007), gps(120.68354));
    bus_stop_detail * bs284_3 = new bus_stop_detail("Taichung  El. School", gps(24.130257), gps(120.685017));
    bus_stop_detail * bs284_4 = new bus_stop_detail("NCHU Affiliated Agricultural Senior High School(Taichung Rd.)", gps(24.12746833), gps(120.6845183));
    bus_stop_detail * bs284_5 = new bus_stop_detail("Tong-Feng Junior High School", gps(24.126369), gps(120.685972));
    bus_stop_detail * bs284_6 = new bus_stop_detail("Renhe-Dazhi Rd. Intersection", gps(24.12636), gps(120.6897767));
    bus_route *br284 = new bus_route("r284", {bs284_1,bs284_2,bs284_3,bs284_4,bs284_5,bs284_6});
    bus_group *bg1 = new bus_group{br281, br284};
    return bg1;
}

extern bool is_equal(ROOT_TYPE *a, ROOT_TYPE *b) {
    std::string strA = dump_object(a);
    std::string strB = dump_object(b);
    if(strA==strB) return true;
    return false;
}

extern std::string dump_object(ROOT_TYPE *root) {
    std::stringstream buf;
    buf << *root ;
    return buf.str();
}

std::ostream & operator<<(std::ostream &os, const gps &gp){
    return os << gp.degrees;
}

std::ostream & operator<<(std::ostream &os, const bus_stop &bs) {
    return os << "lat:" << bs.latitude << " lng:" << bs.longitude << " " << bs.description();
}

std::ostream & operator<<(std::ostream &os, const bus_route &br) {
    os << "route_name:" << br.route_name << std::endl;
    for (auto itr=br.routes.begin(); itr!=br.routes.end(); itr++) {
        os << **itr << std::endl;
    }
    return os;
}

std::ostream & operator<<(std::ostream &os, const bus_group &bg) {
    for (auto itr=bg.groups.begin(); itr!=bg.groups.end(); itr++) {
        os << **itr << std::endl;
    }
    return os;
}
