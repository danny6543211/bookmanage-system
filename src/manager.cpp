#include "manager.h"
#include <string>

manager::manager() {}

void manager::add_book(std::string book_name)
{
    book_libary::add_book(book_name);
}

void manager::delete_book(std::string book_name)
{
    book_libary::delete_book(book_name);
}