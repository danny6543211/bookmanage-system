#ifndef BOOK_LIBRARY_H
#define BOOK_LIBRARY_H
#include <string>
#include <cstring>
#include <database_base.hpp>

// 對圖書数据库進行操作
class book_library : private database_base
{
public:
    book_library();

    ~book_library();

    // 添加書           
    void add_book(std::string book_name);
    
    // 查詢是否有書  
    int check_book(std::string book_name);

    // 查詢書狀態 返回状态
    int book_status(std::string book_name);

    // 改變書狀態
    void change_book_status(std::string book_name, int new_status);
    
    // 删除书
    void delete_book(std::string book_name);

    // 透过字段查询有啥书
    std::string search_book(std::string keyword);

    // 獲取book的ID
    std::string get_book_id(std::string book_name);

private:

};

#endif