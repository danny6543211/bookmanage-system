#include <iostream>
#include <string>
#include <sqlite3.h>
#include "sqlite_api.h"

data_base::data_base(int select_table_name) {
    table_name = select_table_name;
    int res = sqlite3_open("test.db", &db);
    if (res) {
        std::cout << "can't npen database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
}
data_base::~data_base()
{
    sqlite3_close(db);
}
bool data_base::add_user(std::string name, int ID)
{
    std::string sql("insert into ");
    if (table_name == 1)
        sql += "users values";
    else if (table_name == 2)
        sql += "books values";
    sql += "('" + name + "', " + std::to_string(ID) + ");";
    std::cout << sql << std::endl;
    char *err_msg;
    int res = sqlite3_exec(db, sql.c_str(), nullptr, 0, &err_msg);
    if (res != SQLITE_OK) {
        std::cout << ":" << err_msg << std::endl;
        return 0;
    }
    return 1;
}