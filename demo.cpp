#include "include/client.h"
#include "include/message.h"

int main()
{
    client test;
    test.set_message(USER, LOG_IN, "danny6543211", "da12345", "test book");
    
    test.client_connect();
    test.send_message();
    std::cout << "服务器返回值:" << test.get_return_value() << std::endl;

    return 0;
}