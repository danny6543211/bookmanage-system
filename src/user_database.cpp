#include <iostream>
#include <cstdlib>
#include <memory>
#include "user_database.h"

static int callback(void *data, int argc, char **argv, char **col_name)
{
    if (argc != 0)
        *(int *)data = 1;
    else
        *(int *)data = 0;
    return 0;
}

user_database::user_database() : database() 
{
    this->choice_database();
}

bool user_database::add_user(std::string account, std::string password)
{
    std::string sql_command("insert into users values");
    sql_command += "('" + account + "','" + password + "')";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

bool user_database::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from users where account == ";
    sql_command += "'" + account + "' and password == '" + password + "';";
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return -1;
    }
    res = *find;
    free(find);
    return res;
}

bool user_database::check_user(std::string account)
{
    std::string sql_command = "select * from users where account == ";
    sql_command += "'" + account + "';";
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return -1;
    }
    res = *find;
    free(find);
    return res;
}

void user_database::choice_database()
{
    int res = sqlite3_open("user_libary.db", &db);
    if (res)
        std::cout << "can't open database: " << sqlite3_errmsg(db) << std::endl;
}