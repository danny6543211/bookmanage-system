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
// #define CHANGE_PASSWORD 4
#define ADD_BOOK        5
#define DELETE_BOOK     6

#define GET_MY_BOOK     7
#define GET_ALL_RENT    8
#define SEARCH_BOOK     9

// #define EDIT_BOOK_INFO  
// #define MANAGE_USER     

// type(用户类型)
#define MANAGER         0
#define USER            1

class message
{
public:
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