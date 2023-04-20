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
    void set_return_buffer(char buffer[BUFFER_SIZE]);
    char *get_return_buffer();
    void set_return_value(int res);
    int get_return_value();
    void send_result();
    int get_type();
    int get_action();
    std::string get_account();
    std::string get_password();
    std::string get_book_name();
    
private:
    message *msg;
    result *_result;
    SOCKET servSock;
    SOCKET clntSock;
};

#endif