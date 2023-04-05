#ifndef CLIENT_H
#define CLIENT_H
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include "message.h"

class client
{
public:
    client();
    ~client();
    // 设定好信息
    void set_message(int type, int action, char *account, char *password, char *book_name);
    // 与服务器连接
    void client_connect();
    // 传递信息到服务器
    int send_message();
    // 取得服务器回传的值
    int get_return_value();
    void test();
private:
    message *msg;
    int *res;
    int server_socket;
    struct sockaddr_in server_address;
};

#endif