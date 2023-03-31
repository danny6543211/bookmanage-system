#pragma once
#include <sqlite3.h>

class database
{
public:
    // 打開數據庫
    database();
    ~database();

protected:
    sqlite3 *db;
};