#include <iostream>
#include <string>
#include <sqlite3.h>
#include "database.h"

// 数据库基类操作
database::database() {}

database::~database()
{
    sqlite3_close(db);
}