#pragma once
#include <sqlite3.h>

//  打開數據庫

class database
{
public:
    database();
    // 打開數據庫
    virtual void choice_database() = 0;
    // 关闭数据库
    ~database();
    
protected:
    sqlite3 *db;
};