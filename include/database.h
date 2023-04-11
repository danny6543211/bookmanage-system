#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include <string>

//  數據庫
class database
{
protected:
    database(std::string database_name);
    // 关闭数据库
    ~database();

protected:
    sqlite3 *db;
};

// 對用户数据库進行操作
class user_libary : private database
{
protected:
    user_libary();
    // 添加帳戶      
    int add_user(std::string account, std::string password);
    // 查詢帳號加密码    
    int check_user(std::string account, std::string password);
    // 查詢帳號        
    int check_user(std::string account);
    // 使用者增加借书数据     
    int add_rent_book(std::string user_name, std::string book_name);
    // 删除借书数据        
    int delete_rent_book(std::string book_name);
};

// 對圖書数据库進行操作
class book_libary : private database
{
protected:
    book_libary();
    // 添加書           
    int add_book(std::string book_name);
    // 查詢是否有書  
    int check_book(std::string book_name);
    // 查詢書狀態 返回状态
    int book_status(std::string book_name);
    // 改變書狀態
    int change_book_status(std::string book_name, int new_status);
    // 删除书
    int delete_book(std::string book_name);
};

#endif