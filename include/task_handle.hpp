#ifndef TASK_HANDLE_H
#define TASK_HANDLE_H
#include <user.h>
#include <manager.h>
#include <visitor.h>
#include <message.hpp>

class task_handle
{
public:
    task_handle() {}

    ~task_handle() {}

    void ask(message msg)
    {
        __message = msg;

        switch (__message.action)
        {
        case LOG_IN:
        {

            visitor visitor;
            visitor.set(__message.data.account, __message.data.password);

            int return_value = visitor.login();
            __result.set_value(return_value);

            if (return_value == 1)
            {
                user_library user_library;
                int type = user_library.get_type(__message.data.account);
                if (type == 1)
                    __result.set_buffer("user");
                else
                    __result.set_buffer("manager");
            }
            else if (return_value == 0)
                __result.set_buffer("Password incorrect");
            else
                __result.set_buffer("Account not exist");

            break;
        }

        case SIGN_UP:
        {
            visitor visitor;
            visitor.set(__message.data.account, __message.data.password);

            int return_value = visitor.sign_up();
            __result.set_value(return_value);

            if (return_value == 1)
                __result.set_buffer("Sign up successful");
            else
                __result.set_buffer("Account already exists");

            break;
        }

        case RENT_BOOK:
        {
            user user;
            user.set(__message.data.account, __message.data.password, __message.data.book_name);

            int return_value = user.rent_book();
            __result.set_value(return_value);

            if (return_value == 1)
                __result.set_buffer("Rent book successful");
            else if (return_value == 0)
                __result.set_buffer("The book has been borrowed");
            else if (return_value == -1)
                __result.set_buffer("There is no such book");

            break;
        }

        case RETURN_BOOK:
        {
            user user;
            user.set(__message.data.account, __message.data.password, __message.data.book_name);

            int return_value = user.return_book();
            __result.set_value(return_value);

            if (return_value == 1)
                __result.set_buffer("Return book successful");
            else
                __result.set_buffer("Book not exist");

            break;
        }

        case GET_MY_BOOK:
        {
            user user;
            user.set(__message.data.account, __message.data.password, __message.data.book_name);

            std::string return_buffer = user.get_my_book();
            __result.set_buffer(user.get_my_book());

            if (return_buffer.empty())
                __result.set_value(0);
            else
                __result.set_value(1);

            break;
        }

        case SEARCH_BOOK:
        {
            user user;
            user.set(__message.data.account, __message.data.password, __message.data.book_name);

            std::string return_buffer = user.search_book(__message.data.book_name);
            __result.set_buffer(return_buffer);

            if (return_buffer.empty())
                __result.set_value(0);
            else
                __result.set_value(1);

            break;
        }

        case ADD_BOOK:
        {
            manager manager;
            manager.set(__message.data.account, __message.data.password, __message.data.book_name);

            int return_value = manager.add_book();
            __result.set_value(return_value);

            if (return_value == 1)
                __result.set_buffer("Add book successful");
            else if (return_value == 0)
                __result.set_buffer("Book exist already");

            break;
        }

        case DELETE_BOOK:
        {
            manager manager;
            manager.set(__message.data.account, __message.data.password, __message.data.book_name);

            __result.set_value(manager.delete_book());
            __result.set_buffer("Delete book successful");

            break;
        }

        default:
        {
            __result.set_value(0);
            __result.set_buffer("Illegel action");

            break;
        }

        // switch end
        }
    }

    result get_result()
    {
        return __result;
    }

private:
    message __message;
    result __result;
};

#endif