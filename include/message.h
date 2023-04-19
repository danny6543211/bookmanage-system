#ifndef MESSAGE_H
#define MESSAGE_H
#include <string>
#include <iostream>

#define ACCOUNT_MAX_SIZE  20
#define PASSWORD_MAX_SIZE 20
#define BOOKNAME_MAX_SIZE 20

// action(操作)
#define LOG_IN          0
#define SIGN_UP         1
#define RENT_BOOK       2
#define RETURN_BOOOK    3
#define CHANGE_PASSWORD 4
#define ADD_BOOK        5
#define DELETE_BOOK     6

// #define EDIT_BOOK_INFO  7
// #define MANAGE_USER     8

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