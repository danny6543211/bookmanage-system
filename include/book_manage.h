#pragma once
#include "book_database.h"
#include <string>

// 館藏管理接口

class book_manage 
{
    book_manage();
    // 
    int rent_book(std::string book_name);
    // 
    int return_book(std::string book_name);

private:
    book_database bookDatabase;
};