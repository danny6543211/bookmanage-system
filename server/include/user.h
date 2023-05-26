#ifndef USER_H
#define USER_H
#include <string>
#include <user_library.h>
#include <book_library.h>

class user
{
public:
    user();

    ~user();

    void set(std::string account, std::string password, std::string book_name);
    
    //  租书            1(成功) 0(已被借走) -1(没这本书)
    int rent_book();
    
    //  还书
    int return_book();
    
    //  查看自己借的書
    std::string get_my_book();
    
    // 查书
    std::string search_book(std::string keyword);

private:
    std::string __account;
    std::string __password;
    std::string __book;

    user_library __user_library;
    book_library __book_library;

};


#endif