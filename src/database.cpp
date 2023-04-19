#include <sqlite3.h>
#include <iostream>
#include <string>
#include <chrono>
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

user_libary::user_libary() : database("user_libary.db") {
    char *err_msg;
    // 檢查數據庫的表
    sqlite3_exec(db, "select * from user_info;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK) {
        std::cout << "error from user_info" << std::endl;
        exit(0);
    } 
    sqlite3_exec(db, "select * from rent_book_table;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK) {
        std::cout << "error from rent_book_table" << std::endl;
        exit(0);
    } 
}

void user_libary::add_user(std::string account, std::string password)
{
    // 計算新的id 從編號0開始
    int new_id = user_id_count();
    std::string sql_command = "insert into user_info (id,account,password,permission) values";
    // 完善sql語句
    sql_command += " (" + std::to_string(new_id) + ",'" + account + "','" + password + "', 1);";
    char *err;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
}

//  查找帳戶的callback
static int callback(void *data, int argc, char **argv, char **col_name)
{
    // 有数据返回1
    if (argc != 0)
        *(int *)data = 1;
    else
        *(int *)data = 0;
    return 0;
}

int user_libary::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "' and password == '" + password + "';";
    int find;
    char *err;
    int res = sqlite3_exec(db, sql_command.c_str(), callback, &find, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
    return find;
}

int user_libary::check_user(std::string account)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "';";
    char *err;
    int find;
    int res = sqlite3_exec(db, sql_command.c_str(), callback, &find, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
    return find;
}

void user_libary::add_rent_book(std::string account, std::string book_name)
{
    // 獲取當前日期時間
    auto now = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(now);
    std::string sql_command = "insert into rent_book_table (account, book_name, date) values";
    sql_command += " ('" + account + "','" + book_name + "', '" + std::string(ctime(&time)) +"');";
    char *err;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
}

void user_libary::delete_rent_book(std::string book_name)
{
    std::string sql_command = "delete from rent_book_table where book_name == ";
    sql_command += "'" + book_name + "';";
    char *err;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
}

void user_libary::change_password(std::string account, std::string new_password)
{   
    std::string sql_command = "update user_info set password = '";
    sql_command += new_password + "' where account = '" + account + "';";
    char *err;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
}

int user_libary::user_id_count()
{
    // 查看回調函數執行多少次就是有多少id
    int count;
    char *err;
    int res = sqlite3_exec(db, "select count(id) from user_info;", [](
        void *data,
        int colCount,
        char **colValue,
        char **colName  
    )->int{
        *(int *)data = std::stoi(std::string(colValue[0]).c_str());
        return 0;
    }, &count, &err);
    return count;
}


// 书的数据库操作
static int book_status_callback(void *data, int argc, char **argv, char **col_name)
{
    *(int *)data = std::stoi(argv[0]);
    return 0;
}

book_libary::book_libary() : database("book_libary.db") 
{
    // 檢查book_libary
    char *err_msg;
    // 檢查數據庫的表
    sqlite3_exec(db, "select * from books;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK) {
        std::cout << "error from books" << std::endl;
        exit(0);
    } 
}

void book_libary::add_book(std::string book_name)
{
    // 從編號0開始
    int new_id_count = book_id_count();
    std::string sql_command("insert into books (id, book_name, status) values");
    sql_command += " ('"+ std::to_string(new_id_count) + "', '" + book_name + "', 1);";
    sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, nullptr);
}

int book_libary::check_book(std::string book_name)
{
    std::string sql_command = "select * from books where book_name == ";
    sql_command += "'" + book_name + "';";
    int find;
    sqlite3_exec(db, sql_command.c_str(), callback, &find, nullptr);
    return find;
}

int book_libary::book_status(std::string book_name)
{
    std::string sql_command = "select status from books where book_name == ";
    sql_command += "'" + book_name + "';";
    int status;
    sqlite3_exec(db, sql_command.c_str(), book_status_callback, &status, nullptr);
    return status;
}

void book_libary::change_book_status(std::string book_name, int new_status)
{
    std::string sql_command = "update books set status = ";
    sql_command += std::to_string(new_status) + " where book_name = '" + book_name + "';";
    sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, nullptr);
}

void book_libary::delete_book(std::string book_name)
{
    std::string sql_command = "delete from books where book_name == '";
    sql_command += book_name + "';";
    sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, nullptr);
}

int book_libary::book_id_count()
{
    int count;
    sqlite3_exec(db, "select count(id) from books;", [](
        void *data,
        int colCount,
        char **colValue,
        char **colName  
    )->int{
        *(int *)data = std::stoi(std::string(colValue[0]).c_str());
        return 0;
    }, &count, nullptr);
    return count;
}