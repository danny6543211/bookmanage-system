#ifndef TASK_HANDLE_H
#define TASK_HANDLE_H
#include <user.h>
#include <manager.h>
#include <visitor.h>
#include <message.hpp>
#include <WinSock2.h>
#include <thread_pool.hpp>

class task_handle
{
public:
    task_handle()
    {
        __thread_pool = new thread_pool(THREAD_COUNT);
    }

    ~task_handle()
    {
        delete __thread_pool;
    }

    void add_task(message msg, SOCKET client_socket)
    {
        // message message;
        // SOCKET cs;
        __thread_pool->enqueue([=]{
        
        // std::cout << message.action;

        result result;
        switch (msg.action)
        {
        case LOG_IN:
        {

            visitor visitor;
            visitor.set(msg.data.account, msg.data.password);

            int return_value = visitor.login();
            result.set_value(return_value);

            if (return_value == 1)
            {
                user_library user_library;
                int type = user_library.get_type(msg.data.account);
                if (type == 1)
                    result.set_buffer("user");
                else
                    result.set_buffer("manager");
            }
            else if (return_value == 0)
                result.set_buffer("Password incorrect");
            else
                result.set_buffer("Account not exist");

            break;
        }

        case SIGN_UP:
        {
            visitor visitor;
            visitor.set(msg.data.account, msg.data.password);

            int return_value = visitor.sign_up();
            result.set_value(return_value);

            if (return_value == 1)
                result.set_buffer("Sign up successful");
            else
                result.set_buffer("Account already exists");

            break;
        }

        case RENT_BOOK:
        {
            user user;
            user.set(msg.data.account, msg.data.password, msg.data.book_name);

            int return_value = user.rent_book();
            result.set_value(return_value);

            if (return_value == 1)
                result.set_buffer("Rent book successful");
            else if (return_value == 0)
                result.set_buffer("The book has been borrowed");
            else if (return_value == -1)
                result.set_buffer("There is no such book");

            break;
        }

        case RETURN_BOOK:
        {
            user user;
            user.set(msg.data.account, msg.data.password, msg.data.book_name);

            int return_value = user.return_book();
            result.set_value(return_value);

            if (return_value == 1)
                result.set_buffer("Return book successful");
            else
                result.set_buffer("Book not exist");

            break;
        }

        case GET_MY_BOOK:
        {
            user user;
            user.set(msg.data.account, msg.data.password, msg.data.book_name);

            std::string return_buffer = user.get_my_book();
            result.set_buffer(user.get_my_book());

            if (return_buffer.empty())
                result.set_value(0);
            else
                result.set_value(1);

            break;
        }

        case SEARCH_BOOK:
        {
            user user;
            user.set(msg.data.account, msg.data.password, msg.data.book_name);

            std::string return_buffer = user.search_book(msg.data.book_name);
            result.set_buffer(return_buffer);

            if (return_buffer.empty())
                result.set_value(0);
            else
                result.set_value(1);

            break;
        }

        case ADD_BOOK:
        {
            manager manager;
            manager.set(msg.data.account, msg.data.password, msg.data.book_name);

            int return_value = manager.add_book();
            result.set_value(return_value);

            if (return_value == 1)
                result.set_buffer("Add book successful");
            else if (return_value == 0)
                result.set_buffer("Book exist already");

            break;
        }

        case DELETE_BOOK:
        {
            manager manager;
            manager.set(msg.data.account, msg.data.password, msg.data.book_name);

            result.set_value(manager.delete_book());
            result.set_buffer("Delete book successful");

            break;
        }

        default:
        {
            result.set_value(0);
            result.set_buffer("Illegel action");

            break;
        }

            // switch end
        }

        // 打印日誌
        log(msg, result);

        // 結果返回給客戶端
        send(client_socket, (char *)&result, sizeof(result), 0);

        });
    }

private:
    thread_pool *__thread_pool;
    message __message;
    result __result;

    void log(message msg, result res)
    {
        Logger logger("./log/log.txt");

        std::string return_value = std::to_string(res.get_return_value());
        if (return_value.size() == 1)
            return_value = " " + return_value;

        std::string infomation = +"" + return_value + "  ";
        infomation += std::string(msg.data.account) + " -> " + get_action_string(msg);

        logger.Log(LogLevel::INFO, infomation);
    }

    std::string get_action_string(message msg)
    {
        std::string action_string;

        switch (msg.action)
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
};

#endif