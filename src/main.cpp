#include "server.h"
#include <iostream>

int main()
{
    server test;
    test.server_listen();
    while (1)
    {
        test.server_accept();
        test.dosomething();
    }

    return 0;
}
