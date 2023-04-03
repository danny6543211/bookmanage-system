#include "user_libary.h"

//  用户数据库的操作
static int callback(void *data, int argc, char **argv, char **col_name)
{
    if (argc != 0)
        *(int *)data = 1;
    else
        *(int *)data = 0;
    return 0;
}

user_libary::user_libary() : database()
{
    this->choice_database();
}

bool user_libary::add_user(std::string account, std::string password)
{
    std::string sql_command("insert into user_info values");
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

bool user_libary::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from user_info where account == ";
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
    std::string sql_command = "select * from user_info where account == ";
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

void user_libary::add_rent_book(std::string user_name, std::string book_name)
{
    std::string sql_command = "insert into rent_book_table values ";
    sql_command += "('" + user_name + "','" + book_name + "');";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
    }
}

void user_libary::delete_rent_book(std::string book_name)
{
    std::string sql_command = "delete from rent_book_table where book_name == ";
    sql_command += "'" + book_name + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
    }
}

void user_libary::choice_database()
{
    int res = sqlite3_open("user_libary.db", &db);
    if (res)
        std::cout << "can't open database: " << sqlite3_errmsg(db) << std::endl;
}