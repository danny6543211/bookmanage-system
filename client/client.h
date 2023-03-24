#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

class client
{
public:
    client();
    // return value -1(error) 0(correct)
    void client_connect();
    void dosomething();

private:
    int server_socket;
    struct sockaddr_in server_address;
};

#endif