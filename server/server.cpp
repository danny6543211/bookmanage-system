#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "server.h"

server::server() {}
void server::server_init()
{
    server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(1234);
    bind(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
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

void server::server_dosomething()
{ 
    char buffer[40];
    read(client_socket, buffer, sizeof(buffer)-1);
       
    printf("%s\n", buffer);
}