#pragma once
#include "database.h"
#include <string>

class book_libary : public database 
{
public:
    book_libary();
    // 添加書
    bool add_book(std::string book_name, int book_status);
    // 查詢書返回狀態
    int check_book(std::string book_name);
    // 改變書狀態
    bool change_book_status(std::string book_name, int new_status);
};