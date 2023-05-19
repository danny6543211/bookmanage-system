#ifndef VISITOR_H
#define VISITOR_H
#include <string>
#include <user_library.h>

class visitor
{
public: 
    visitor();

    ~visitor();

    void set(std::string account, std::string password);

    int login();

    int sign_up();

private:
    std::string __account;
    std::string __password;

    user_library user_library;

};

#endif