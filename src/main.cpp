#include <server.h>

int main()
{
    server server;
    
    while (1)
    {
        server.server_accept();

        server.receive_message();
        
        server.run_task();

        server.log();

        server.send_result();

        server.flush_buffer();

    }

    return 0;
}