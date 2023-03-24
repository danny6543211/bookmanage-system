#ifndef DATA_BASE
#define DATA_BASE
#include <sqlite3.h>
// 數據庫編號
#define BOOKS 0
#define USERS 1


class data_base 
{
public: 
    // db_ID = 要操作的數據庫 
    data_base(int db_ID);
private:
    sqlite3 *db;
};

#endif