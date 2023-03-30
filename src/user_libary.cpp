#include <iostream>
#include <cstdlib>
#include <memory>
#include "user_libary.h"

static int callback(void *data, int argc, char **argv, char **col_name)
{
    if (argc == 2)
    {
        *(int *)data = 1;
    }
    else
        *(int *)data = 0;
    return 0;
}

user_libary::user_libary() : database() {}

bool user_libary::add_user(std::string account, std::string password)
{
    std::string sql_command("insert into user_table values");
    sql_command += "('" + account + "','" + password + "')";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, 0, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

bool user_libary::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from user_table where account == ";
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

bool user_libary::check_user(std::string account)
{
}

int main()
{
    user_libary test;
    // test.add_user("danny", "123123");
    test.check_user("danny", "123123");
    return 0;
}