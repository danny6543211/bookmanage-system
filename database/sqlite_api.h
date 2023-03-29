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
    data_base();
    ~data_base();
private:
    sqlite3 *db;
};

#endif