#include "user.h"
#include <string>
#include <iostream>
#include <cstdio>

user::user() {}

void user::init(std::string account, std::string password, std::string book_name)
{
    _account = account;
    _password = password;
    _book_name = book_name;
}

int user::log_in()
{
    if (userLibary.check_user(_account))
    {
        return userLibary.check_user(_account, _password);
    }
    return -1;
}

int user::sign_up()
{
    if (userLibary.check_user(_account)) 
        return 0;
    else
        userLibary.add_user(_account, _password);
    return 1;
}

int user::rent_book()
{
    if (bookLibary.check_book(_book_name))
    {
        if (bookLibary.book_status(_book_name))
        {
            bookLibary.change_book_status(_book_name, 0);
            userLibary.add_rent_book(_account, _book_name);
            return 1;
        }
        else
            // status = 0 書被借走了
            return 0;
    }
    // 沒這本書
    return -1;
}

void user::return_book()
{
    if (bookLibary.check_book(_book_name) && (bookLibary.book_status(_book_name) == 1))
    {
        bookLibary.change_book_status(_book_name, 1);
        userLibary.delete_rent_book(_book_name);
    }
    
}

// int user::change_password(std::string account, std::string new_password)
// {
//     user_libary::change_password(account, new_password);
//     return 1;
// }

std::string user::get_my_book()
{
    return userLibary.get_my_rent_book(_account);
}

void user::refresh_buffer()
{
    
}