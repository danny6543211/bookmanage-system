#include <iostream>
#include <winsock2.h>
#include <string>
#include "server_socket.h"
#pragma comment (lib, "ws2_32.lib")  //加载 ws2_32.dll


server::server()
{
    WSADATA wsaData;
    WSAStartup( MAKEWORD(2, 2), &wsaData);

    servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    
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

    closesocket(clntSock);
    closesocket(servSock);

    WSACleanup();

    delete msg;
}

void server::server_listen()
{
    listen(servSock, 20);
}

void server::server_accept()
{
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
}

void server::receive_message()
{
    recv(clntSock, (char *)msg, sizeof(*msg), 0);
    std::cout << "receive_message:" << std::endl << *msg;
}

void server::send_value_to_client()
{
    int *temp = new int;
    *temp = _res;
    send(clntSock, (char *)temp, sizeof(int), 0);
    delete (temp);
}

void server::set_result(int res)
{
    _res = res;
}

int server::get_type()
{
    user_libary userLibary;
    return userLibary.get_type(msg->data.account);
}    

int server::get_action()
{
    return msg->action;
}

std::string server::get_account()
{
    return std::string(msg->data.account);
}

std::string server::get_password()
{
    return std::string(msg->data.password);
}

std::string server::get_book_name()
{  
    return std::string(msg->data.book_name);
}