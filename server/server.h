#ifndef SERVER_H
#define SERVER_H

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
};

#endif