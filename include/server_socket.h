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
    void set_result(int res);
    int get_type();
    int get_action();
    std::string get_account();
    std::string get_password();
    std::string get_book_name();
    
private:
    message *msg;
    int _res; 
    SOCKET servSock;
    SOCKET clntSock;
};

#endif