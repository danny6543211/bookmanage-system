#include "client_socket.h"

int main()
{
    client test;
    test.client_connect();
    test.set_message(USER, LOG_IN, "test_account", "test_password", "");
    test.send_message();

    std::cout << test.get_return_value() << std::endl;

    return 0;
}