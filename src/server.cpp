#include <iostream>
#include <winsock2.h>
#include "server.h"
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


server::server()
{
    //初始化 DLL
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);

    //创建套接字
    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
    //绑定套接字
    struct sockaddr_in sockAddr;
    memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
    sockAddr.sin_family = PF_INET;  //使用IPv4地址
    sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
    sockAddr.sin_port = htons(1234);  //端口
    bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));

    msg = new message;
}

server::~server()
{

    //关闭套接字
    closesocket(clntSock);
    closesocket(servSock);

    //终止 DLL 的使用
    WSACleanup();

    delete msg;
}

void server::server_listen()
{
    //进入监听状态
    listen(servSock, 20);
}

void server::server_accept()
{
    //接收客户端请求
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
}

void server::receive_message()
{
    recv(clntSock, (char *)msg, sizeof(*msg), 0);
    std::cout << "receive_message:" << std::endl << *msg;
    if (msg->type == 1)
    {
        user user;
        switch (msg->action)
        {
        case LOG_IN:
            res = user.log_in(msg->data.account, msg->data.password);
            break;
        case SIGN_UP:
            res = user.sign_up(msg->data.account, msg->data.password);
            break;
        case RENT_BOOK:
            res = user.rent_book(msg->data.book_name, msg->data.account);
            break;
        case RETURN_BOOOK:
            user.return_book(msg->data.book_name);
            res = 1;
            break;
        }
    }
    else if (msg->type == 0)
    {
        manager manager;
    }
}

void server::send_value_to_client()
{
    int *temp = new int;
    *temp = res;
    send(clntSock, (char *)temp, sizeof(int), 0);
    delete (temp);
}
