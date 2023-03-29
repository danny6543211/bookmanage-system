#pragma once
#include "database.h"
#include <string>

class user_libary : public database 
{
public:
    user_libary();
    bool add_user(std::string account, std::string password);

};

