#ifndef MESSAGE_HPP
#define MESSAGE_HPP
#include <string>
#include <iostream>
#include <cstring>

#define ACCOUNT_MAX_SIZE 64
#define PASSWORD_MAX_SIZE 64
#define BOOKNAME_MAX_SIZE 64
#define RESULT_BUFFER_SIZE 512

// action(操作)
#define LOG_IN 0
#define SIGN_UP 1
#define RENT_BOOK 2
#define RETURN_BOOK 3
// #define CHANGE_PASSWORD 4
#define ADD_BOOK 5
#define DELETE_BOOK 6
#define GET_MY_BOOK 7
// #define GET_ALL_RENT 8
#define SEARCH_BOOK 9

// #define EDIT_BOOK_INFO
// #define MANAGE_USER

// type(用户类型)
#define MANAGER 0
#define USER 1

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

public:
    message() : action(-1)
    {
        strcpy(data.account, "");
        strcpy(data.password, "");
        strcpy(data.book_name, "");
    }

    ~message() {}

    void flush()
    {
        action = -1;
        memset(&data, 0, sizeof(data));
    }

    friend std::ostream &operator<<(std::ostream &out, message &msg)
    {
        out << "action:" << msg.action << std::endl;
        out << "account:" << msg.data.account << std::endl;
        out << "password:" << msg.data.password << std::endl;
        out << "book name:" << msg.data.book_name << std::endl;
        return out;
    }
};

class result
{
public:
    result() 
    {
        set_value(-2);
        set_buffer("");
    }
    
    ~result() {}
public:
    // 給服務器用的 
    void set_buffer(std::string buffer)
    {
        strcpy(__buffer, buffer.c_str());
    }
    
    void set_value(int value)
    {
        __value = value;
    }
    
    // 給客戶端用的 
    int get_return_value()
    {
        return __value;
    }
    
    std::string get_return_buffer()
    {
        return __buffer;
    }

    // 刷新
    void flush()
    {
        set_value(-2);
        set_buffer("");
    }

private:
    int __value;
    char __buffer[RESULT_BUFFER_SIZE];
};

#endif