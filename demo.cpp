#include "client_socket.h"
#include <string>
#include <cstring>
#include <cstdlib> 

int main()
{
    client test1;

    char account[20] = "test_account";
    char password[20] = "test_password";
    char book[20] = "";

    test1.send_message(LOG_IN, account, password, book);
    std::cout << test1.get_return_value() << std::endl;

    return 0;
}