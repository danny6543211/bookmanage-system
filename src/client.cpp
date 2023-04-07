#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <memory>
#include "../include/client.h"
#include "../include/message.h"

client::client()
{
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = htons(1234);

    msg = new message;
    res = new int;
}
client::~client()
{
    delete(msg);
    delete(res);
    close(server_socket);
}
void client::client_connect()
{
    int res = connect(server_socket, (struct sockaddr *)&server_address, sizeof(server_address));
    if (res == -1)
        std::cout << "error" << std::endl;
}
void client::set_message(int type, int action, char *account, char *password, char *book_name)
{
    msg->type = type;
    msg->action = action;
    strcpy(msg->data.account, account);
    strcpy(msg->data.password, password);
    strcpy(msg->data.book_name, book_name);

}
int client::send_message()
{
    write(server_socket, msg, sizeof(*msg));
}
int client::get_return_value()
{
    read(server_socket, res, sizeof(int));   
    return *res;
}
void client::test()
{
    
}