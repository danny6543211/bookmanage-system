#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <iostream>

//  打開數據庫
class database
{
protected:
    database();
    // 打開數據庫
    virtual void choice_database() = 0;
    // 关闭数据库
    ~database();

protected:
    sqlite3 *db;
};

#endif