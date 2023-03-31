#pragma once
#include "database.h"
#include <string>

// 對數據庫使用者表進行操作

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