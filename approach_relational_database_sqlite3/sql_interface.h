
#ifndef SQL_Interface
#define SQL_Interface
#include "data.hpp"
#include <sqlite3.h>

class sql_interface
{
private:
    sqlite3*    _db;
public:
    sql_interface(const char* filepath);
    ~sql_interface();

    void add_schema();
    void serialize(ROOT_TYPE* root);
    ROOT_TYPE* deserialize();
};

sql_interface::sql_interface(const char* filepath)
{
    sqlite3_open(filepath, &_db);
}

sql_interface::~sql_interface()
{
    sqlite3_close(_db);
}


#endif