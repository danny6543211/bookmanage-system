#pragma once
#include <sqlite3.h>

class database
{
public:
    database();
    ~database();

protected:
    sqlite3 *db;
};