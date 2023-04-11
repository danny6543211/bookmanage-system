#ifndef SERVER_H
#define SERVER_H
#include <winsock2.h>
#include "user.h"
#include "manager.h"
#include "message.h"


class server
{
public:
    server();
    ~server();
    void server_listen();
    void server_accept();
    void receive_message();
    void send_value_to_client();
private:
    int res;
    SOCKET servSock;
    SOCKET clntSock;
    message *msg;
};

#endif