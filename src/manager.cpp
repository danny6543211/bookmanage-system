#include "manager.h"
#include <string>
#include <iostream>

manager::manager() {}

void manager::init(std::string account, std::string password, std::string book_name)
{
    _account = account;
    _password = password;
    _book_name = book_name;
}

void manager::add_book()
{
    if (!bookLibary.check_book(_book_name))
        bookLibary.add_book(_book_name);
}

void manager::delete_book()
{
    bookLibary.delete_book(_book_name);
}