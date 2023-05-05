#ifndef MANAGER_H
#define MANAGER_H
#include "database.h"

class manager
{
public:
    manager();
    // 初始化
    void init(std::string account, std::string password, std::string book_name);
    int log_in();
    // 增加书
    int add_book();
    // 删除书
    int delete_book();

private:
    user_libary userLibary;
    book_libary bookLibary;

    std::string _account;
    std::string _password;
    std::string _book_name;
};

#endif