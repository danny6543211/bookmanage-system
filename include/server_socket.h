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
    // 接收客戶端請求
    void server_accept();
    // 接收客戶端消息
    void receive_message();
    // 設定返回字符串
    void set_return_buffer(char buffer[BUFFER_SIZE]);
    // 返回字符串
    char *get_return_buffer();
    // 設定返回值
    void set_return_value(int res);
    // 獲取返回值
    int get_return_value();
    // 返回值傳給客戶端
    void send_result();
    // 取得用戶類型 0 = manager, 1 = user
    int get_type();
    // 取得客戶端想要進行的操作
    int get_action();
    // 取得客戶端傳送的信息
    std::string get_account();
    std::string get_password();
    std::string get_book_name();
    
private:
    // 客戶端的信信息
    message *msg;
    // 要返回的結果
    result *_result;
    // socket 套接字
    SOCKET servSock;
    SOCKET clntSock;
};

#endif