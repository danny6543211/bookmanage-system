#include "client_socket.h"
#include "database.h"
#include <string>
#include <cstring>
#include <cstdlib> 
#include <windows.h>

int main()
{
    // 管理员账号
    char manager_account[ACCOUNT_MAX_SIZE] = "danny456258";
    char manager_password[PASSWORD_MAX_SIZE] = "da123456";
    
    // 正常账号
    char user_account[20] = "test_account";
    char user_password[20] = "test_password";
    
    // 测试书名
    char book1[20] = "test_book1";
    char book2[20] = "test_book2";
    
    // 透过test字段搜索
    char book3[20] = "book2";


    client test;
    // 登陆
    test.send_message(LOG_IN, "test_account", "123", "test");
    // 返回值
    std::cout << "value:" << test.get_return_value() << std::endl;
    // 返回的字符串
    std::cout << "buffer:" << std::endl << test.get_return_buffer() << std::endl;

    system("pause");

    return 0;
}