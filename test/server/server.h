#ifndef SERVER_H
#define SERVER_H
#include "user_manage.h"

class server
{
public:
    server();
    void server_listen();
    void server_accept();
    void server_dosomething();

private:
    int server_socket;
    int client_socket;
    user_manage userManage;
};

#endif