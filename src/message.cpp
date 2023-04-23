#include "message.h"

std::ostream &operator <<(std::ostream &out, message &msg)
{
    out << "action:" << msg.action << std::endl;
    out << "account:" << msg.data.account << std::endl;
    out << "password:" << msg.data.password << std::endl;
    out << "book name:" << msg.data.book_name << std::endl;
    return out;
}

void message::empty_message()
{
    action = 0;
    strcpy(data.account, "");
    strcpy(data.password, "");
    strcpy(data.book_name, "");
}









result::result() 
{
    _value = -1;
}

void result::set_buffer(std::string buffer)
{
    strcpy(_buffer, buffer.c_str());
}

void result::set_value(int value)
{
    _value = value;
}

int result::get_return_value()
{
    return _value;
}

std::string result::get_return_buffer()
{
    return std::string(_buffer);
}