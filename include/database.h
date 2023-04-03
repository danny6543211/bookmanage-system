#ifndef DATABASE_H
#define DATABASE_H
#include <sqlite3.h>
#include <iostream>

//  打開數據庫
class database
{
protected:
    database();
    // 打開數據庫
    virtual void choice_database() = 0;
    // 关闭数据库
    ~database();

protected:
    sqlite3 *db;
};

// 對圖書数据库進行操作
class book_database : private database
{
protected:
    book_database();
    // 添加書
    void add_book(std::string book_name, int book_status);
    // 查詢是否有書
    int check_book(std::string book_name);
    // 查詢書狀態
    int book_status(std::string book_name);
    // 改變書狀態
    void change_book_status(std::string book_name, int new_status);
    // 借书信息录入借书表

private:
    void choice_database();
};

// 對用户数据库進行操作
class user_database : private database
{
protected:
    user_database();
    // 添加帳戶
    bool add_user(std::string account, std::string password);
    // 查詢帳號加密碼(用於登陸)
    bool check_user(std::string account, std::string password);
    // 查詢帳號(用於註冊)
    bool check_user(std::string account);
    // 使用者增加借书数据
    void add_rent_book(std::string user_name, std::string book_name);
    // 删除借书数据
    void delete_rent_book(std::string book_name);

private:
    void choice_database();
};

#endif