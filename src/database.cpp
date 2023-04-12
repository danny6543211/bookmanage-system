#include <sqlite3.h>
#include <iostream>
#include <string>
#include "database.h"


// 数据库基类操作
database::database(std::string database_name) 
{
    sqlite3_open(database_name.c_str(), &db);
}

database::~database()
{
    sqlite3_close(db);
}


//  用户数据库的操作
static int callback(void *data, int argc, char **argv, char **col_name)
{
    // 有数据返回1
    if (argc != 0)
        *(int *)data = 1;
    else
        *(int *)data = 0;
    return 0;
}

user_libary::user_libary() : database("user_libary.db") {}

int user_libary::add_user(std::string account, std::string password)
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

int user_libary::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "' and password == '" + password + "';";
  
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    res = *find;
    free(find);
    return res;
}

int user_libary::check_user(std::string account)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "';";
   
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    res = *find;
    free(find);
    return res;
}

int user_libary::add_rent_book(std::string user_name, std::string book_name)
{
    std::string sql_command = "insert into rent_book_table values ";
    sql_command += "('" + user_name + "','" + book_name + "');";
  
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

int user_libary::delete_rent_book(std::string book_name)
{
    std::string sql_command = "delete from rent_book_table where book_name == ";
    sql_command += "'" + book_name + "';";
    
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

int user_libary::change_password(std::string account, std::string new_password)
{   
    std::string sql_command = "update user_info set password = '";
    sql_command += account + "' where account = '" + new_password + "';";

    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}


// 书的数据库操作
static int book_status_callback(void *data, int argc, char **argv, char **col_name)
{
    *(int *)data = std::stoi(argv[0]);
    return 0;
}

book_libary::book_libary() : database("book_libary.db") {}

int book_libary::add_book(std::string book_name)
{
    std::string sql_command("insert into books values");
    sql_command += "('" + book_name + "', 1)";
   
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, 0, &err_msg);
    if (res != SQLITE_OK)
    {    
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

int book_libary::check_book(std::string book_name)
{
    std::string sql_command = "select * from books where book_name == ";
    sql_command += "'" + book_name + "';";
   
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    res = *find;
    free(find);
    return res;
}

int book_libary::book_status(std::string book_name)
{
    std::string sql_command = "select status from books where book_name == ";
    sql_command += "'" + book_name + "';";
  
    char *err_msg;
    int *status = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), book_status_callback, status, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    res = *status;
    free(status);
    return res;
}

int book_libary::change_book_status(std::string book_name, int new_status)
{
    std::string sql_command = "update books set status = ";
    sql_command += std::to_string(new_status) + " where book_name = '" + book_name + "';";
   
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}

int book_libary::delete_book(std::string book_name)
{
    std::string sql_command = "delete from books where book_name == '";
    sql_command += book_name + "';";
  
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return 0;
    }
    return 1;
}