#include "client_socket.h"

int main()
{
    client test;
    test.client_connect();
    test.set_message(MANAGER, DELETE_BOOK, "danny456258", "da123456", "testbook");
    test.send_message();


    std::cout << test.get_return_value() << std::endl;

    return 0;
}