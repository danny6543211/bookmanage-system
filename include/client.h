#ifndef CLIENT_H
#define CLIENT_H
#include "message.h"
#include <unistd.h>
#include <WinSock2.h>

class client
{
public:
    client();
    ~client();
    // 与服务器连接
    void client_connect();
    // 设定好信息
    void set_message(int type, int action, char *account, char *password, char *book_name);
    // 传递信息到服务器
    int send_message();
    // 取得服务器回传的值
    int get_return_value();

private:
    message *msg;
    int *res;
    SOCKET sock;
};

#endif