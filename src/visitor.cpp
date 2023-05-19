#include <visitor.h>

visitor::visitor()
{
}

visitor::~visitor()
{
}

void visitor::set(std::string account, std::string password)
{
    __account = account;
    __password = password;
}

int visitor::login()
{
    if (user_library.check_user(__account))
    {
        return user_library.check_user(__account, __password);
    }
    return -1;
}

int visitor::sign_up()
{
    // 已有帳戶註冊失敗
    if (user_library.check_user(__account))
        return 0;
    else 
        user_library.add_user(__account, __password);
    return 1;
}
