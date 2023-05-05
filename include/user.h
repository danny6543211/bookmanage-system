#ifndef USER_H
#define USER_H
#include <string>
#include "database.h"

//  使用者管理接口
class user
{
public:
    user();
    // 初始化
    void init(std::string account, std::string password, std::string book_name);
    //  用戶登陸         1(登陸成功) 0(密碼錯誤) -1(沒有此帳戶)
    int log_in();
    //  用戶註冊         1(註冊成功) 0(已有此帳號)
    int sign_up();
    //  租书            1(成功) 0(已被借走) -1(没这本书)
    int rent_book();
    //  还书
    int return_book();
    //  更改密码
    // int change_password(std::string account, std::string new_password);
    //  查看自己借的書
    std::string get_my_book();
    // 查书
    std::string search_book(std::string keyword);
    
private:
    user_libary userLibary;
    book_libary bookLibary;

    std::string _account;
    std::string _password;
    std::string _book_name;
};

#endif