#include <iostream>
#include <string>
#include <sqlite3.h>
#include "database.h"

database::database()
{
    // 默認數據庫->libary.db
    int res = sqlite3_open("libary.db", &db);
    if (res)
    {
        std::cout << "can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
}
database::~database()
{
    sqlite3_close(db);
}
