#include "client_socket.h"
#include "database.h"
#include <string>
#include <cstring>
#include <cstdlib> 

int main()
{
    client test;
    
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
    char book3[20] = "test";

    // 查看借的书
    test.send_message(GET_MY_BOOK, user_account, user_password, "");
    // 返回值
    std::cout << "value:" << test.get_return_value() << std::endl;
    // 返回的字符串
    std::cout << "buffer:" << std::endl << test.get_return_buffer() << std::endl;

    return 0;
}