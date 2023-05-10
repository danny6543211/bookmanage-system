#include "client_socket.h"
#include "database.h"
#include <string>
#include <cstring>
#include <cstdlib> 
#include <windows.h>
#include <vector>


std::vector<std::string> foo(std::string str)
{
    std::vector<std::string> res;
    std::string::iterator it_l = str.begin();
    std::string::iterator it_r = str.begin();

    while (*it_r != '\0')
    {
        if (*it_r == '\n')
        {
            res.push_back(std::string(it_l, (it_r)));
            it_l = it_r+1;
        }
        it_r++;
    }

    return res;
}

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

    client test;
 

    test.send_message(SEARCH_BOOK, "danny456258", "da123456", "test");
    
    
    // foo 把 string 分段成 vector<string> 

    // std::vector<std::string> res = foo(test.get_return_buffer());
    // // 打印查询结果
    // for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
    // {
    //     std::cout << *it << std::endl;
    // }
    std::cout << test.get_return_buffer() << std::endl;

    system("pause");

    return 0;
}