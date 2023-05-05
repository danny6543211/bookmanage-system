#include <iostream>
#include <winsock2.h>
#include <string>
#include "server.h"
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
    _result = new result;

    listen(servSock, 20);
}

server::~server()
{
    WSACleanup();
    closesocket(clntSock);
    closesocket(servSock);


    delete(msg);
    delete(_result);
}

void server::server_accept()
{
    std::cout << "accept" << std::endl;
    SOCKADDR clntAddr;
    int nSize = sizeof(SOCKADDR);
    clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
}

void server::receive_message()
{
    recv(clntSock, (char *)msg, sizeof(*msg), 0);
    std::cout << "receive_message:" << std::endl << *msg;
}

void server::server_close()
{   
    msg->empty_message();
    _result->set_buffer("");
}

void server::send_result()
{
    send(clntSock, (char *)_result, sizeof(*_result), 0);
}

void server::set_return_value(int res)
{
    _result->set_value(res);
}

int server::get_type()
{
    user_libary userLibary;
    return userLibary.get_type(std::string(msg->data.account));
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

void server::set_return_buffer(std::string buffer)
{
    _result->set_buffer(buffer);
}

std::string server::get_return_buffer()
{
    return _result->get_return_buffer();
}

int server::get_return_value()
{
    return _result->get_return_value();
}