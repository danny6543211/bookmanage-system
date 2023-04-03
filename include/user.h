#ifndef USER_H
#define USER_H
#include "database.h"
#include <string>

//  使用者管理接口
class user : private user_database, book_database
{
public:
    user();
    // 用戶登陸         return  1:登陸成功 0:密碼錯誤 -1:沒有此帳戶
    int log_in(std::string account, std::string password);
    // 用戶註冊         return  1:註冊成功 0:已有此帳號
    int sign_up(std::string account, std::string password);
    
    //  租书    return 1:成功 0:已被借走 -1:没这本书
    int rent_book(std::string book_name, std::string user_name);
    //  还书
    void return_book(std::string book_name);
};

#endif