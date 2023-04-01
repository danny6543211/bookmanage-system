#include "user_manage.h"
#include <string>

user_manage::user_manage() {}

int user_manage::log_in(std::string account, std::string password)
{   
    if (userDatabase.check_user(account))
    {
        if (userDatabase.check_user(account, password))
            return 1;
        else
            return 0;
    }
    return -1;
}

int user_manage::sign_up(std::string account, std::string password)
{
    if (userDatabase.check_user(account))
        return 0;
    else 
    {
        userDatabase.add_user(account, password);
        return 1;
    }
}