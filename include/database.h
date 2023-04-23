#ifndef DATABASE_H
#define DATABASE_H
#include "sqlite3.h"
#include "message.h"
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
public:
    user_libary();
    // 添加帳戶      
    void add_user(std::string account, std::string password);
    // 查詢帳號加密码    
    int check_user(std::string account, std::string password);
    // 查詢帳號        
    int check_user(std::string account);
    // 使用者增加借书数据     
    void add_rent_book(std::string user_name, std::string book_name);
    // 删除借书数据        
    void delete_rent_book(std::string book_name);
    // 更改密码
    void change_password(std::string account, std::string new_password);
    // 查詢使用者權限
    int get_type(std::string account);
    // 查看借書表
    std::string get_my_rent_book(std::string account);
    
private:
    // 用於新增id
    int user_id_count();
    int get_user_id(std::string account);
    int get_book_id(std::string book_name);
};

// 對圖書数据库進行操作
class book_libary : private database
{
public:
    book_libary();
    // 添加書           
    void add_book(std::string book_name);
    // 查詢是否有書  
    int check_book(std::string book_name);
    // 查詢書狀態 返回状态
    int book_status(std::string book_name);
    // 改變書狀態
    void change_book_status(std::string book_name, int new_status);
    // 删除书
    void delete_book(std::string book_name);
private:
    int book_id_count();
};

#endif