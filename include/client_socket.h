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
    void set_message(int action, char *account, char *password, char *book_name);
    // 传递信息到服务器
    void send_message();
    // 取得服务器回传的值
    int get_return_value();
    // 取得服務器回傳的數據
    char *get_return_buffer();

private:
    message *msg;
    result *_result;
    SOCKET sock;
};

#endif