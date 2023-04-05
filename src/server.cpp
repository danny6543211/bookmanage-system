#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <memory>
#include <string>
#include <iostream>
#include "server.h"

server::server()
{
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(1234);
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));

    msg = new message;
}
server::~server()
{
    close(server_socket);
    close(client_socket);
    delete(msg);
}
void server::server_listen()
{
    listen(server_socket, 5);
}
void server::server_accept()
{
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    client_socket = accept(server_socket, (struct sockaddr *)&clnt_addr, &clnt_addr_size);
}

void server::receive_message()
{
    read(client_socket, msg, sizeof(*msg));
    std::cout << "receive_message:" << std::endl << *msg;
    if (msg->type == 1)
    {
        user user;
        switch (msg->action)
        {
        case LOG_IN:
            res = user.log_in(msg->data.account, msg->data.password);
            break;
        case SIGN_UP:
            res = user.sign_up(msg->data.account, msg->data.password);
            break;
        case RENT_BOOK:
            res = user.rent_book(msg->data.book_name, msg->data.account);
            break;
        case RETURN_BOOOK:
            user.return_book(msg->data.book_name);
            res = 1;
            break;
        }
    }
    else if (msg->type == 0)
    {
        manager manager;
    }
}

void server::send_value_to_client()
{
    int *temp = new int;
    *temp = res;
    write(client_socket, temp, sizeof(int));
}

void server::test()
{
    user u;
    std::cout << u.sign_up("danny6543211", "da123456") ;
}