#include "client_socket.h"
#include <string>

int main()
{
    client test;
    test.client_connect();
    char account[20] = "test_account";
    char password[20] = "test_password";
    char book[20] = "testbook";
    test.set_message(LOG_IN, account, password, book);
    // test.set_message(MANAGER, ADD_BOOK, account, password, book);
    test.send_message();

    std::cout << test.get_return_value() << std::endl;

    return 0;
}