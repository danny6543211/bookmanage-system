#include <iostream>
#include <sqlite3.h>

int main()
{
    sqlite3 *db;
    sqlite3_open("test.db", &db);

    sqlite3_close(db);
}