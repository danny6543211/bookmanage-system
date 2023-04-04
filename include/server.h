#ifndef SERVER_H
#define SERVER_H
#include "user.h"
#include "manager.h"
#include "message.h"

class server
{
public:
    server();
    void server_listen();
    void server_accept();
    void dosomething();

private:
    int server_socket;
    int client_socket;
    user user;
    manager manager;

};

#endif