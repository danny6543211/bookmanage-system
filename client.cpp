#include <iostream>
#include <cstdlib>
#include <WinSock2.h>
#include "client.h"
#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll


client::client()
{
    //初始化DLL
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    //创建套接字
    sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    msg = new message;
}

client::~client()
{
    //关闭套接字
    closesocket(sock);
    //终止使用 DLL
    WSACleanup();

    delete(msg);
}

void client::client_connect()
{
    //向服务器发起请求
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    sockAddr.sin_port = htons(1234);
    connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
}

void client::set_message(int type, int action, char *account, char *password, char *book_name)
{
    msg->type = type;
    msg->action = action;
    strcpy(msg->data.account, account);
    strcpy(msg->data.password, password);
    strcpy(msg->data.book_name, book_name);
    std::cout << *msg << std::endl;
}

int client::send_message()
{
    send(sock, (char *) msg, sizeof(*msg), 0);
}

int client::get_return_value()
{
    char buffer[32];
    recv(sock, buffer, sizeof(buffer), 0);
    return *(int*)buffer;
}