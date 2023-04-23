#include <iostream>
#include <cstdlib>
#include <WinSock2.h>
#include "client_socket.h"
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll


client::client()
{
    msg = new message;
    _result = new result;
}

client::~client()
{
    delete(msg);
    delete(_result);
}

void client::send_message(int action, char *account, char *password, char *book_name)
{
    msg->action = action;
    strcpy(msg->data.account, account);
    strcpy(msg->data.password, password);
    strcpy(msg->data.book_name, book_name);
 
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    //向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
    
    send(sock, (char *) msg, sizeof(*msg), 0);
    recv(sock, (char *) _result, sizeof(*_result), 0);  

    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();
    
}

int client::get_return_value()
{
    return _result->get_return_value();
}

std::string client::get_return_buffer()
{
    return _result->get_return_buffer();
}