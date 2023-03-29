#include <iostream>
#include "../include/user_libary.h"

user_libary::user_libary():database() {}

bool user_libary::add_user(std::string account, std::string password)
{
    std::string sql_command("insert into user_table values");
    sql_command += "('" + account + "','" + password + "')";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, 0, &err_msg);
    if (res != SQLITE_OK) {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

int main()
{
    user_libary test;
    test.add_user("danny2", "123123");
    return 0;
}