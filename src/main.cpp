#include "server_socket.h"

int main()
{
    server test;
    test.server_listen();
    while (1)
    {
        test.server_accept();
        test.receive_message();
        if (test.msg->type == 1)
        {
            user user;
            switch (test.msg->action)
            {
            case LOG_IN:
                test.res = user.log_in(test.msg->data.account, test.msg->data.password);
                break;
            case SIGN_UP:
                test.res = user.sign_up(test.msg->data.account, test.msg->data.password);
                break;
            case RENT_BOOK:
                test.res = user.rent_book(test.msg->data.book_name, test.msg->data.account);
                break;
            case RETURN_BOOOK:
                user.return_book(test.msg->data.book_name);
                test.res = 1;
                break;
            case CHANGE_PASSWORD:
                test.res = user.change_password(test.msg->data.account, test.msg->data.password);
                break;
            default:
                test.res = 0;
                std::cout << "error action" << std::endl;
            }
        }
        else if (test.msg->type == 0)
        {
            manager manager;
            switch (test.msg->action)
            {
            case ADD_BOOK:
                manager.add_book(test.msg->data.book_name);
                test.res = 1;
                break;
            case DELETE_BOOK:
                manager.delete_book(test.msg->data.book_name);
                test.res = 1;
                break;
            }
        }
        test.send_value_to_client();
    }

    return 0;
}