#pragma once
#include "user_table.h"
#include <string>

//  使用者管理接口

class user_manage
{
public:
    user_manage();
    // 用戶登陸         return  1:登陸成功 0:密碼錯誤 -1:沒有此帳戶
    int log_in(std::string account, std::string password);
    // 用戶註冊         return  1:註冊成功 0:已有此帳號
    int sign_up(std::string account, std::string password);

private:
    // 用於操作user數據表
    user_table userTable;
};