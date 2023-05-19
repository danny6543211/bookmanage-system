#include <user.h>

user::user()
{
}

user::~user()
{
}

void user::set(std::string account, std::string password, std::string book_name)
{
    __account = account;
    __password = password;
    __book = book_name;
}

//  租书            1(成功) 0(已被借走) -1(没这本书)
int user::rent_book()
{
    if (__book_library.check_book(__book))
    {
        if (__book_library.book_status(__book) == 1)
        {
            __book_library.change_book_status(__book, 0);
            __user_library.add_rent_book(__account, __book);
            return 1;
        }
        // 被借走了
        else 
            return 0;
    }
    // 沒此書
    return -1;
}

//  还书
int user::return_book()
{
    if (__book_library.check_book(__book) )
    {
        __book_library.change_book_status(__book, 1);
        __user_library.delete_rent_book(__book);
        return 1;
    }
    // 没这本书
    return 0;
}


//  查看自己借的書
std::string user::get_my_book()
{
    return __user_library.get_my_rent_book(__account);
}


// 查书
std::string user::search_book(std::string keyword)
{
    return __book_library.search_book(keyword);
}