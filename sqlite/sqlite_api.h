#ifndef DATA_BASE
#define DATA_BASE
#include <sqlite3.h>
#include <string>
// 數據庫表編號
#define USERS_TABLE 1
#define BOOKS_TABLE 2


class data_base 
{
public: 
    data_base(int select_table_name);
    ~data_base();
    bool add_user(std::string name, int ID);
    // bool check_user();
private:
    sqlite3 *db;
    int table_name;
};

#endif