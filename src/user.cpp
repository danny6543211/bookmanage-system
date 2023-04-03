#include "user.h"
#include <string>

user_manage::user_manage() {}

int user_manage::log_in(std::string account, std::string password)
{
    if (this->check_user(account))
    {
        if (this->check_user(account, password))
            return 1;
        else
            return 0;
    }
    return -1;
}

int user_manage::sign_up(std::string account, std::string password)
{
    if (this->check_user(account))
        return 0;
    else
    {
        this->add_user(account, password);
        return 1;
    }
}

int user_manage::rent_book(std::string book_name, std::string user_name)
{
    if (this->book_status(book_name) == 1)
    {
        this->change_book_status(book_name, 0);
        this->add_rent_book(user_name, book_name);
        return 1;
    }

    if (this->book_status(book_name) == 0)
        return 0;
    return -1;
}

void user_manage::return_book(std::string book_name)
{
    this->change_book_status(book_name, 1);
    this->delete_rent_book(book_name);
}