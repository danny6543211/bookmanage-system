#include "server_socket.h"
#include <string>

int main()
{
    server server;
    user user;
    manager manager;
    server.server_listen();
    while (1)
    {
        server.server_accept();
        server.receive_message();
        int type = server.get_type();
        if (type == USER)
        {
            user.init(server.get_account(), server.get_password(), server.get_book_name());
            switch (server.get_action())
            {
            case LOG_IN:
                server.set_result(user.log_in());
                break;
            case SIGN_UP:
                server.set_result(user.sign_up());
                break;
            case RENT_BOOK:
                server.set_result(user.rent_book());
                break;
            case RETURN_BOOOK:
                user.return_book();
                server.set_result(1);
                break;
            // case CHANGE_PASSWORD:
            //     server.res = user.change_password();
            //     break;
            default:
                server.set_result(0);
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
                server.set_result(1);
                break;
            case DELETE_BOOK:
                manager.delete_book();
                server.set_result(1);
                break;
            default:
                server.set_result(0);
                std::cout << "error action" << std::endl;
                break;
            }
        }
        server.send_value_to_client();
    }

    return 0;
}