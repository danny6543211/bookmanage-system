#include <server.h>

int main()
{
    server server;
    
    while (1)
    {
        server.accept_message();
        
        server.run_task();

    }

    return 0;
}