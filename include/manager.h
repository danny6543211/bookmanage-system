#ifndef MANAGER_H
#define MANAGER_H
#include "user_libary.h"
#include "book_libary.h"

class manager : private user_libary, book_libary
{
public:
    manager();
    // 增加书
    void add_book(std::string book_name);
    // 删除书
    void delete_book(std::string book_name);
};

#endif