#ifndef MANAGER_H
#define MANAGER_H
#include <user_library.h>
#include <book_library.h>

class manager
{
public:
    manager();
    
    ~manager();

    void set(std::string account, std::string password, std::string book_name);

    // 增加书
    int add_book();

    // 删除书
    int delete_book();

private:
    std::string __account;
    std::string __password;
    std::string __book;
    
    user_library __user_library;
    book_library __book_library;
};

#endif