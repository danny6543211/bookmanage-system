#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include "client.h"

client::client() {
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(1234);
}
void client::client_connect()
{
    connect(server_socket, (struct sockaddr*)&server_address, sizeof(server_address));
}
void client::dosomething()
{
    char *str = "hello";
    write(server_socket, str, sizeof(str));

}