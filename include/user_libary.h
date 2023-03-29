#pragma once
#include "database.h"
#include <string>

class user_libary : public database 
{
public:
    user_libary();
    // 添加帳戶
    bool add_user(std::string account, std::string password);
    // 查詢帳戶
    
};