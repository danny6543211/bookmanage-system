#include "client_socket.h"
#include <string>
#include <cstring>
#include <cstdlib> 

int main()
{
    client test1;
    test1.client_connect();
    char account[20] = "test_account";
    char password[20] = "test_password";
    char book[20] = "";

    test1.client_connect();
    test1.set_message(LOG_IN, account, password, book);
    test1.send_message();
    std::cout << test1.get_return_value() << std::endl;

    return 0;
}