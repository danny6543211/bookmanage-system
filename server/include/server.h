#ifndef SERVER_H
#define SERVER_H
#include <message.hpp>
#include <task_handle.hpp>
#include <winsock2.h>

class server
{
public:
    server();
    
    ~server();

    // 接受客戶端請求
    void accept_message();

    // 處理請求
    void run_task();

    // 刷新信息
    void flush_buffer();

private:
    // 客戶端的信息
    message *__message;
    // 要返回的結果
    result *__result;
    // 任務句柄
    task_handle __task_handle;
    
    // socket 套接字
    SOCKET __server_socket;
    SOCKET __client_socket;

};


#endif