#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <iostream>

#define ACCOUNT_MAX_SIZE 16
#define PASSWORD_MAX_SIZE 16
#define BOOKNAME_MAX_SIZE 16

// action(操作)
#define LOG_IN          0
#define SIGN_UP         1
#define EDIT_USER_INFO  2
#define RENT_BOOK       3
#define RETURN_BOOOK    4
#define ADD_BOOK        5
#define EDIT_BOOK_INFO  6
#define MANAGE_USER     7

// type(用户类型)
#define MANAGER         0
#define USER            1

class message
{
public:
    int type;
    int action;
    struct
    {
        char account[ACCOUNT_MAX_SIZE];
        char password[PASSWORD_MAX_SIZE];
        char book_name[BOOKNAME_MAX_SIZE];
    } data;
    friend std::ostream &operator <<(std::ostream &out, message &msg);
};

#endif