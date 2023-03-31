#pragma once
#include "database.h"
#include <string>

class user_table : public database
{
public:
    user_table();
    // 添加帳戶
    bool add_user(std::string account, std::string password);
    // 查詢帳號加密碼(用於登陸)
    bool check_user(std::string account, std::string password);
    // 查詢帳號(用於註冊)
    bool check_user(std::string account);
};