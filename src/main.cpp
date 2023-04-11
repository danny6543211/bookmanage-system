#include "server.h"


int main()
{
    server test;
    test.server_listen();
    int res;
    while (1)
    {
        test.server_accept();
        test.receive_message();
        test.send_value_to_client();
    }

    return 0;
}