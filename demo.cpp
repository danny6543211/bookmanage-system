#include "client.h"

int main()
{
    client test;
    test.set_message(USER, LOG_IN, "danny456258", "da123456", "");
    test.client_connect();
    test.send_message();
    std::cout << test.get_return_value() << std::endl;

    return 0;
}