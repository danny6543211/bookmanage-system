#ifndef DATABASE_HPP
#define DATABASE_HPP
#include <sqlite3.h>
#include <log.hpp>
#include <string>

class database_base
{
protected:

    sqlite3 *__db;
    
    std::string __database_name;

    database_base(const std::string &database_name) : __database_name(database_name)
    {   
        Logger database_log("./log/log.txt");
        
        int result = sqlite3_open(__database_name.c_str(), &__db);
        if (result != SQLITE_OK)
            database_log.Log(LogLevel::ERROR, sqlite3_errmsg(__db));
    }

    ~database_base()
    {
        Logger database_log("./log/log.txt");
        
        int result = sqlite3_close(__db);
        if (result != SQLITE_OK) 
            database_log.Log(LogLevel::ERROR, sqlite3_errmsg(__db));
    }

};


#endif