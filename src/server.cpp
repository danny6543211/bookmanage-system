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

void server::server_accept()
{
    SOCKADDR client_address;
    int nSize = sizeof(SOCKADDR);
    __client_socket = accept(__server_socket, (SOCKADDR *)&client_address, &nSize);
}

void server::receive_message()
{
    recv(__client_socket, (char *)__message, sizeof(*__message), 0);
}

void server::run_task()
{
    __task_handle.ask(*__message);
    *__result = __task_handle.get_result();
}

void server::log()
{
    Logger logger("./log/log.txt");

    std::string return_value = std::to_string(__result->get_return_value());
    if (return_value.size() == 1)
        return_value = " " + return_value;

    std::string infomation = + "(" + return_value + ") ";
    infomation += std::string(__message->data.account) + " -> " + get_action_string();

    logger.Log(LogLevel::INFO, infomation);
    
}

void server::send_result()
{
    send(__client_socket, (char *)__result, sizeof(*__result), 0);
}

void server::flush_buffer()
{
    __message->flush();
    __result->flush();
}

std::string server::get_action_string()
{
    std::string action_string;
 
    switch (__message->action)
    {
    case LOG_IN:
        action_string = "log in";
        break;
    case SIGN_UP:
        action_string = "sign up";
        break;
    case RENT_BOOK:
        action_string = "rent book";
        break;
    case RETURN_BOOK:
        action_string = "return book";
        break;
    case ADD_BOOK:
        action_string = "add book";
        break;
    case DELETE_BOOK:
        action_string = "delete book";
        break;
    case GET_MY_BOOK:
        action_string = "get user's rent book";
        break;
    case SEARCH_BOOK:
        action_string = "search book";
        break;
    default:
        action_string = "illigel action";
        break;
    } 

    return action_string;
}