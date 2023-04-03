#ifndef USER_LIBARY_H
#define USER_LIBARY_H
#include "database.h"

// 對用户数据库進行操作
class user_libary : private database
{
protected:
    user_libary();
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