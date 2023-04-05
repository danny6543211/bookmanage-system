#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "message.h"

class client
{
public:
    client();
    ~client();
    void client_connect();
    void set_message(int type, int action, char *account, char *password, char *book_name);
    int send_message();
    int get_return_value();
    void test();
private:
    message *msg;
    int *res;
    int server_socket;
    struct sockaddr_in server_address;
};

#endif