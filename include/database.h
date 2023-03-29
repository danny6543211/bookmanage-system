#pragma once
#include <sqlite3.h>
#include <string>
// 數據庫表編號
#define USERS_TABLE 1
#define BOOKS_TABLE 2


class database 
{
public: 
    database();
    ~database();
protected:
    sqlite3 *db;
};