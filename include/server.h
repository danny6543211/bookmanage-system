#ifndef SERVER_H
#define SERVER_H
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
    void test();
    int res;
private:
    int server_socket;
    int client_socket;
    message *msg;
};

#endif