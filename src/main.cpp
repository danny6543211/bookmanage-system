#include "server_socket.h"
#include <string>

int main()
{
    server server;
    user user;
    manager manager;
    
    while (1)
    {
        server.server_accept();
        server.receive_message();
        // 查看是管理員還是普通用戶
        int type = server.get_type();
        if (type == USER)
        {
            user.init(server.get_account(), server.get_password(), server.get_book_name());
            switch (server.get_action())
            {
            case LOG_IN:
                server.set_return_value(user.log_in());
                break;
            case SIGN_UP:
                server.set_return_value(user.sign_up());
                break;
            case RENT_BOOK:
                server.set_return_value(user.rent_book());
                break;
            case RETURN_BOOOK:
                user.return_book();
                server.set_return_value(1);
                break;
            // case CHANGE_PASSWORD:
                
            //     break;
            case GET_MY_BOOK:
                server.set_return_value(strlen(server.get_return_buffer()));
                server.set_return_buffer(user.get_my_book());
                break;
            default:
                server.set_return_value(0);
                std::cout << "error action" << std::endl;
            }
        }
        else if (type == MANAGER)
        {
            manager.init(server.get_account(), server.get_password(), server.get_book_name());
            switch (server.get_action())
            {
            case ADD_BOOK:
                manager.add_book();
                server.set_return_value(1);
                break;
            case DELETE_BOOK:
                manager.delete_book();
                server.set_return_value(1);
                break;
            default:
                server.set_return_value(0);
                std::cout << "error action" << std::endl;
                break;
            }
        }
        else 
        {
            server.set_return_value(-1);
            server.set_return_buffer("error account");
        }

        server.send_result();
    }

    return 0;
}