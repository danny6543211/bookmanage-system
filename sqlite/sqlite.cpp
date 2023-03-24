#include <iostream>
#include <sqlite3.h>
#include "sqlite.h"

data_base::data_base(int db_ID)
{
    sqlite3 *db;
    if (db_ID == 0) {
        sqlite3_open("books.db", &db);
    } else if (db_ID == 1) {
        sqlite3_open("users.db", &db);
    }



    
}
