#pragma once
#include "database.h"
#include <string>

class book_libary : public database 
{
public:
    book_libary();
    // 添加書
    int add_book(std::string book_name, int book_status);
    // 查詢是否有書
    int check_book(std::string book_name);
    // 查詢書狀態
    int book_status(std::string book_name);
    // 改變書狀態
    void change_book_status(std::string book_name, int new_status);
};