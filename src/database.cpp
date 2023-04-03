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

// 书的数据库操作
static int check_book_callback(void *data, int argc, char **argv, char **col_name)
{
    if (argc != 0)
        *(int *)data = 1;
    else
        *(int *)data = 0;
    return 0;
}

static int book_status_callback(void *data, int argc, char **argv, char **col_name)
{
    *(int *)data = std::stoi(argv[0]);
    return 0;
}

book_database::book_database()
{
    this->choice_database();
}

void book_database::add_book(std::string book_name, int book_status)
{
    std::string sql_command("insert into books values");
    sql_command += "('" + book_name + "'," + std::to_string(book_status) + ")";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, 0, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

int book_database::check_book(std::string book_name)
{
    std::string sql_command = "select * from books where bookname == ";
    sql_command += "'" + book_name + "';";
    char *err_msg;
    int *find = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), check_book_callback, find, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return -1;
    }
    res = *find;
    free(find);
    return res;
}

int book_database::book_status(std::string book_name)
{
    std::string sql_command = "select status from books where bookname == ";
    sql_command += "'" + book_name + "';";
    char *err_msg;
    int *status = (int *)calloc(1, sizeof(int));
    int res = sqlite3_exec(db, sql_command.c_str(), book_status_callback, status, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
        return -1;
    }
    res = *status;
    free(status);
    return res;
}

void book_database::change_book_status(std::string book_name, int new_status)
{
    std::string sql_command = "update books set status = ";
    sql_command += std::to_string(new_status) + " where bookname = '" + book_name + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
    {
        std::cout << err_msg << std::endl;
    }
}

void book_database::choice_database()
{
    int res = sqlite3_open("book_libary.db", &db);
    if (res)
        std::cout << "can't open database: " << sqlite3_errmsg(db) << std::endl;
}

//  用户数据库的操作
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

bool user_database::check_user(std::string account, std::string password)
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

bool user_database::check_user(std::string account)
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

void user_database::add_rent_book(std::string user_name, std::string book_name)
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

void user_database::delete_rent_book(std::string book_name)
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

void user_database::choice_database()
{
    int res = sqlite3_open("user_libary.db", &db);
    if (res)
        std::cout << "can't open database: " << sqlite3_errmsg(db) << std::endl;
}