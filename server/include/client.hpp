#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <string>
#include <message.hpp>
#include <WinSock2.h>

class client
{
public:
    client()
    {
        __message = new message;
        __result = new result;
    }

    ~client()
    {
        delete (__message);
        delete (__result);
    }

    // 传递信息到服务器
    void send_message(int action, char *account, char *password, char *book_name)
    {
        __message->action = action;
        strcpy(__message->data.account, account);
        strcpy(__message->data.password, password);
        strcpy(__message->data.book_name, book_name);

        // 初始化DLL
        WSADATA wsaData;
        WSAStartup(MAKEWORD(2, 2), &wsaData);
        // 创建套接字
        __socket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

        // 向服务器发起请求
        struct sockaddr_in sockAddr;
        memset(&sockAddr, 0, sizeof(sockAddr)); // 每个字节都用0填充
        sockAddr.sin_family = PF_INET;
        sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        sockAddr.sin_port = htons(1234);
        connect(__socket, (SOCKADDR *)&sockAddr, sizeof(SOCKADDR));

        send(__socket, (char *)__message, sizeof(*__message), 0);
        recv(__socket, (char *)__result, sizeof(*__result), 0);

        // 关闭套接字
        closesocket(__socket);
        // 终止使用 DLL
        WSACleanup();
    }

    // 取得服务器回传的值
    int get_return_value()
    {
        return __result->get_return_value();
    }

    // 取得服務器回傳的數據
    std::string get_return_buffer()
    {
        return __result->get_return_buffer();
    }

private:
    message *__message;
    result *__result;
    SOCKET __socket;
};

#endif