#include <iostream>
#include "client.h"

int main()
{
    client obj;
    obj.client_init();
    obj.client_connect();
    obj.dosomething();
    return 0;
}