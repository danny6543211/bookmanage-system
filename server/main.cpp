#include "server.h"

int main()
{
    server obj;
    obj.server_init();
    obj.server_listen();
    while (1) {
        obj.server_accept();
        obj.server_dosomething();
    }

    return 0;
}