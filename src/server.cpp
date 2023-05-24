#include <server.h>

// listen 1234端口
server::server()
{
    WSADATA wsaData;
    WSAStartup(MAKEWORD(2, 2), &wsaData);

    __server_socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    struct sockaddr_in socket_address;
    memset(&socket_address, 0, sizeof(socket_address));      // 每个字节都用0填充
    socket_address.sin_family = PF_INET;                     // 使用IPv4地址
    socket_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // 具体的IP地址
    socket_address.sin_port = htons(1234);                   // 端口
    bind(__server_socket, (SOCKADDR *)&socket_address, sizeof(SOCKADDR));

    __message = new message;
    __result = new result;

    listen(__server_socket, 20);
}

server::~server()
{
    WSACleanup();
    closesocket(__client_socket);
    closesocket(__server_socket);

    delete (__message);
    delete (__result);
}

void server::accept_message()
{
    SOCKADDR client_address;
    int nSize = sizeof(SOCKADDR);
    __client_socket = accept(__server_socket, (SOCKADDR *)&client_address, &nSize);

    recv(__client_socket, (char *)__message, sizeof(*__message), 0);
}

void server::run_task()
{
    // 交給別人處理
    __task_handle.add_task(*__message, __client_socket);
}

void server::flush_buffer()
{
    __message->flush();
    __result->flush();
}