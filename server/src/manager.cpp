#include <manager.h>

manager::manager()
{

}

manager::~manager()
{

}


void manager::set(std::string account, std::string password, std::string book_name)
{
    __account = account;
    __password = password;
    __book = book_name;
}

// 增加书
int manager::add_book()
{
    if (!__book_library.check_book(__book))
    {
        __book_library.add_book(__book);
        return 1;
    }
    return 0;
}

// 删除书
int manager::delete_book()
{
    __book_library.delete_book(__book);
    return 1;
}