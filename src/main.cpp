#include "server.h"
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
        // 註冊帳號
        int return_value = -2;
        int type = server.get_type();

        // 沒有此帳戶查看是否要註冊
        if (type == -1)
        {
            if (server.get_action() == SIGN_UP)
            {
                user.init(server.get_account(), server.get_password(), server.get_book_name());
                return_value = user.sign_up();
                if (return_value == 1)
                    server.set_return_buffer("sign up successful");
                else if (return_value == 0)
                    server.set_return_buffer("account exist already");
                std::cout << "type:visitor" << std::endl;
            }
            else 
            {
                std::cout << "type:account not exist" << std::endl;
            }
        }

        // 查看是管理員還是普通用戶
        if (type == USER)
            std::cout << "type:user" << std::endl;
        else if (type == MANAGER)
            std::cout << "type:manager" << std::endl;

        if (type == USER)
        {
            user.init(server.get_account(), server.get_password(), server.get_book_name());
            switch (server.get_action())
            {
            case LOG_IN:
                return_value = user.log_in();
                server.set_return_value(return_value);
                if (return_value == 0)
                    server.set_return_buffer("password error");
                else if (return_value == 1)
                    server.set_return_buffer("user");
                break;
            case SIGN_UP:
                return_value = user.sign_up();
                server.set_return_value(return_value);
                if (return_value == 1)
                    server.set_return_buffer("sign up successful");
                else if (return_value == 0)
                    server.set_return_buffer("account exist already");
                break;
            case RENT_BOOK:
                return_value = user.rent_book();
                server.set_return_value(return_value);
                if (return_value == 1)
                    server.set_return_buffer("rent book successful");
                else if (return_value == 0)
                    server.set_return_buffer("the book has been borrowed");
                else if (return_value == -1)
                    server.set_return_buffer("there is no such book");
                break;
            case RETURN_BOOOK:
                server.set_return_value(user.return_book());
                server.set_return_buffer("return book successful");
                break;
            case GET_MY_BOOK:
                server.set_return_buffer(user.get_my_book());
                server.set_return_value(1);
                break;
            case SEARCH_BOOK:
                server.set_return_buffer(user.search_book(server.get_book_name()));
                server.set_return_value(1);
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
            case LOG_IN:
                user.init(server.get_account(), server.get_password(), server.get_book_name());
                return_value = user.log_in();
                server.set_return_value(return_value);
                if (return_value == 0)
                    server.set_return_buffer("password error");
                else if (return_value == 1)
                    server.set_return_buffer("manager");
                break;
            case ADD_BOOK:
                return_value = manager.add_book();
                server.set_return_value(return_value);
                if (return_value == 1)
                    server.set_return_buffer("add book successful");
                else if (return_value == 0)
                    server.set_return_buffer("book exist already");
                break;
            case DELETE_BOOK:
                server.set_return_value(manager.delete_book());
                server.set_return_buffer("delete book successful");
                break;
            case SEARCH_BOOK:
                user.init(server.get_account(), server.get_password(), server.get_book_name());
                server.set_return_buffer(user.search_book(server.get_book_name()));
                server.set_return_value(1);
                break;
            default:
                server.set_return_value(0);
                server.set_return_buffer("illegel action");
                std::cout << "error action" << std::endl;
                break;
            }
        }

        std::cout << "return value:" << server.get_return_value() << std::endl;
        std::cout << "return buffer:\n"
                  << server.get_return_buffer() << std::endl;
        server.send_result();
        server.server_close();

        std::cout << std::endl;
    }

    return 0;
}