#include "client_socket.h"
#include "database.h"
#include <string>
#include <cstring>
#include <cstdlib> 

int main()
{
    client test;
    
    char manager_account[ACCOUNT_MAX_SIZE] = "danny456258";
    char manager_password[PASSWORD_MAX_SIZE] = "da123456";
    
    char user_account[20] = "test_account";
    char user_password[20] = "test_password";
    
    char book1[20] = "test_book1";
    char book2[20] = "test_book2";

    // test.send_message(DELETE_BOOK, manager_account, manager_password, book1);
    // test.send_message(DELETE_BOOK, manager_account, manager_password, book2);

    // test.send_message(ADD_BOOK, manager_account, manager_password, book1);
    // test.send_message(ADD_BOOK, manager_account, manager_password, book2);

    // test.send_message(RENT_BOOK, user_account, user_password, book1);
    // test.send_message(RENT_BOOK, user_account, user_password, book2);
    test.send_message(GET_MY_BOOK, user_account, user_password, book2);
    std::cout << test.get_return_buffer() << std::endl;
    std::cout << test.get_return_value() << std::endl;

    // user_libary user;
    // printf("%s", user.get_my_rent_book(std::string(user_account)));
    // std::cout << user.get_my_rent_book(std::string(user_account)) << std::endl;


    return 0;
}