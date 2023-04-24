#include <sqlite3.h>
#include <iostream>
#include <string>
#include <chrono>
#include "database.h"
#include "message.h"

// 数据库基类操作
database::database(std::string database_name)
{
    sqlite3_open(database_name.c_str(), &db);
}

database::~database()
{
    sqlite3_close(db);
}

user_libary::user_libary() : database("user_libary.db")
{
    char *err_msg;
    // 檢查數據庫的表
    sqlite3_exec(db, "select * from user_info;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK)
    {
        std::cout << "error from user_info" << std::endl;
        exit(0);
    }
    sqlite3_exec(db, "select * from rent_book_table;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK)
    {
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
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

int user_libary::check_user(std::string account, std::string password)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "' and password == '" + password + "';";
    int find = 0;
    char *err;
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(int *)data = 1;
        return 0; },
        &find, &err);
    if (res != SQLITE_OK)
        std::cout << err << std::endl;
    return find;
}

int user_libary::check_user(std::string account)
{
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "';";
    char *err_msg;
    // 如果callback 被調用find改成1
    int find = 0;
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        // 有数据返回1
        *(int *)data = 1;
        return 0; },
        &find, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return find;
}

void user_libary::add_rent_book(std::string account, std::string book_name)
{
    // 獲取當前日期時間
    auto now = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(now);
    char *temp = ctime(&time);
    temp[strlen(temp) - 1] = '|';
    std::string sql_command = "insert into rent_book_table (account, book_name, date) values";
    sql_command += " ('" + account + "','" + book_name + "', '" + std::string(temp) + "');";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

void user_libary::delete_rent_book(std::string book_name)
{
    std::string sql_command = "delete from rent_book_table where book_name == ";
    sql_command += "'" + book_name + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

void user_libary::change_password(std::string account, std::string new_password)
{
    std::string sql_command = "update user_info set password = '";
    sql_command += new_password + "' where account = '" + account + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

int user_libary::user_id_count()
{
    // 查看回調函數執行多少次就是有多少id
    int count = 0;
    char *err_msg;
    int res = sqlite3_exec(
        db, "select count(id) from user_info;", [](void *data, int colCount, char **colValue, char **colName) -> int
        {
        *(int *)data = std::stoi(std::string(colValue[0]).c_str());
        return 0; },
        &count, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return count;
}

int user_libary::get_type(std::string account)
{
    char *err_msg;
    // -1表示沒有此帳戶
    int type = -1;
    std::string sql_command = "select * from user_info where account == ";
    sql_command += "'" + account + "';";
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(int *)data = std::stoi(std::string(argv[0]).c_str());
        return 0; },
        &type, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return type;
}

std::string user_libary::get_my_rent_book(std::string account)
{
    char *err_msg;
    char buffer[BUFFER_SIZE] = "";
    // 返回借書數據
    std::string sql_command = "select * from rent_book_table where account == ";
    sql_command += "'" + account + "';";
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        strcat((char *)data, argv[0]);
        strcat((char *)data, " ");
        strcat((char *)data, argv[1]);
        strcat((char *)data, " ");
        strcat((char *)data, argv[2]);
        strcat((char *)data, "\n");
        return 0; },
        buffer, &err_msg);
    buffer[strlen(buffer) - 1] = '\0';
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return std::string(buffer);
}

book_libary::book_libary() : database("book_libary.db")
{
    // 檢查book_libary
    char *err_msg;
    // 檢查數據庫的表
    sqlite3_exec(db, "select * from books;", nullptr, 0, &err_msg);
    if (err_msg != SQLITE_OK)
    {
        std::cout << "error from books" << std::endl;
        exit(0);
    }
}

void book_libary::add_book(std::string book_name)
{
    // 從編號0開始
    // std::cout << book_name << std::endl;
    int new_id_count = book_id_count();
    std::string sql_command("insert into books (id, book_name, status) values");
    sql_command += " ('" + std::to_string(new_id_count) + "', '" + book_name + "', 1);";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

int book_libary::check_book(std::string book_name)
{
    std::string sql_command = "select * from books where book_name == ";
    sql_command += "'" + book_name + "';";
    char *err_msg;
    bool find = 0;
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(bool *)data = 1;
        return 0; },
        &find, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return find;
}

int book_libary::book_status(std::string book_name)
{
    std::string sql_command = "select status from books where book_name == ";
    sql_command += "'" + book_name + "';";
    int status = -1;
    char *err_msg;
    int res = sqlite3_exec(
        db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(int *)data = std::stoi(argv[0]);
        return 0; },
        &status, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return status;
}

void book_libary::change_book_status(std::string book_name, int new_status)
{
    std::string sql_command = "update books set status = ";
    sql_command += std::to_string(new_status) + " where book_name = '" + book_name + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

void book_libary::delete_book(std::string book_name)
{
    std::string sql_command = "delete from books where book_name == '";
    sql_command += book_name + "';";
    char *err_msg;
    int res = sqlite3_exec(db, sql_command.c_str(), nullptr, nullptr, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
}

int book_libary::book_id_count()
{
    int count = 0;
    char *err_msg;
    int res = sqlite3_exec(
        db, "select count(id) from books;", [](void *data, int colCount, char **colValue, char **colName) -> int
        {
        *(int *)data = std::stoi(std::string(colValue[0]).c_str());
        return 0; },
        &count, &err_msg);
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;
    return count;
}

std::string book_libary::search_book(std::string keyword){
    std::string sql = "select * from books where book_name like '%";
    sql += keyword + "%';";
    char buffer[BUFFER_SIZE] = "";
    char *err_msg;
    int res = sqlite3_exec(db, sql.c_str(), [](void *data, int colCount, char **colValue, char **colName) -> int
    {
        strcat((char *)data, colValue[1]);
        strcat((char *)data, " ");
    return 0; },
    buffer, &err_msg);
    buffer[strlen(buffer)-1] = '\0';
    if (res != SQLITE_OK)
        std::cout << err_msg << std::endl;   
    return std::string(buffer);
}