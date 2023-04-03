#ifndef BOOK_LIBARY
#define BOOK_LIBARY
#include "database.h"
// 對圖書数据库進行操作
class book_libary : private database
{
protected:
    book_libary();
    // 添加書
    void add_book(std::string book_name, int book_status);
    // 查詢是否有書
    int check_book(std::string book_name);
    // 查詢書狀態
    int book_status(std::string book_name);
    // 改變書狀態
    void change_book_status(std::string book_name, int new_status);
    // 删除书
    void delete_book(std::string book_name);

private:
    void choice_database();
};

#endif