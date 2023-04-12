#include "user.h"
#include <string>

user::user() {}

int user::log_in(std::string account, std::string password)
{
    if (check_user(account))
    {
        return check_user(account, password);
    }
    // 没有此帐户
    return -1;
}

int user::sign_up(std::string account, std::string password)
{
    if (check_user(account))
        return 0;
    else
        return add_user(account, password);

}

int user::rent_book(std::string book_name, std::string user_name)
{
    if (check_book(book_name))
    {
        if (book_status(book_name))
        {
            change_book_status(book_name, 0);
            add_rent_book(user_name, book_name);
            return 1;
        }
        else
            return 0;
    }
    return -1;
}

void user::return_book(std::string book_name)
{
    change_book_status(book_name, 1);
    delete_rent_book(book_name);
}

int user::change_password(std::string account, std::string new_password)
{
    return user_libary::change_password(account, new_password);
}