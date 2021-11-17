#include <sstream>
#include "data.hpp"
#include "sql_interface.h"

void sql_interface::add_schema() {
    std::string schema = "CREATE TABLE BUS_STOP( \
        ID      INT PRIMARY KEY NOT NULL, \
        NAME    TEXT            NOT NULL, \
        LAT     REAL            NOT NULL, \
        LNG     REAL            NOT NULL  \
        ); \
        CREATE TABLE BUS_ROUTE( \
        ID      INT PRIMARY KEY NOT NULL, \
        NAME    TEXT            NOT NULL, \
        ROUTE   TEXT            NOT NULL \
        );";
    int rc = sqlite3_exec(_db, schema.c_str(), 0, 0, 0);
}

void sql_interface::serialize(ROOT_TYPE *root) {
    int rc;
    int bs_idx = 1;
    int br_idx = 1;
    for(unsigned i=0; i<root->groups.size(); i++) {
        std::stringstream bs_seq;
        for(unsigned j=0; j<root->groups[i]->routes.size(); j++) {
            bs_seq << " " << bs_idx;
            bus_stop_detail* bs = (bus_stop_detail*)root->groups[i]->routes[j];
            std::stringstream sql;
            sql << "INSERT INTO BUS_STOP (ID, NAME, LAT, LNG) VALUES (";
            sql << bs_idx++ << ",'" << bs->stop_name << "'," << bs->latitude << "," << bs->longitude;
            sql << ");";
            rc = sqlite3_exec(_db, sql.str().c_str(), 0, 0, 0);
        }
        std::stringstream br_sql;
        bus_route* br = root->groups[i];
        br_sql << "INSERT INTO BUS_ROUTE (ID, NAME, ROUTE) VALUES (";
        br_sql << br_idx++ << ",'" << br->route_name << "','" << bs_seq.str() << "'";
        br_sql << ");";
        rc = sqlite3_exec(_db, br_sql.str().c_str(), 0, 0, 0);
    }
}

std::string serialize(ROOT_TYPE *root) {
    std::string buf("data.db");
    sql_interface db(buf.c_str());
    db.add_schema();
    db.serialize(root);
    return buf;
}

/*Global variable for callback*/
std::vector<bus_stop_detail*>   bs_vec(1, NULL);
std::vector<bus_route*>         br_vec(1, NULL);

int bs_callback(void *data, int argc, char **argv, char **azColName){
    double lat, lng;
    lat = atof(argv[1]);
    lng = atof(argv[2]);
    bus_stop_detail* bs = new bus_stop_detail(argv[0],gps(lat), gps(lng));
    bs_vec.push_back(bs);
    return 0;
}

int br_callback(void *data, int argc, char **argv, char **azColName){
    std::stringstream buf;
    bus_route* br = new bus_route(argv[0], {});
    buf << argv[1];
    while(!buf.eof()) {
        int idx;
        buf >> idx;
        bus_stop* bs = bs_vec[idx];
        br->routes.push_back(bs);
    }
    br_vec.push_back(br);
    return 0;
}

ROOT_TYPE* sql_interface::deserialize() {
    std::string bs = "SELECT NAME, LAT, LNG FROM BUS_STOP;";
    int rc = sqlite3_exec(_db, bs.c_str(), bs_callback, 0, 0);
    std::string br = "SELECT NAME, ROUTE FROM BUS_ROUTE;";
    rc = sqlite3_exec(_db, br.c_str(), br_callback, 0, 0);
    bus_group* bg = new bus_group();
    for(unsigned i=1; i<br_vec.size(); i++) {
        bg->groups.push_back(br_vec[i]);
    }
    return bg;
}

ROOT_TYPE* deserialize(std::string buf) {
    sql_interface db(buf.c_str());
    ROOT_TYPE *root = db.deserialize();
    return root;
}
