#include "message.h"

std::ostream &operator <<(std::ostream &out, message &msg)
{
    out << "action:" << msg.action << std::endl;
    out << "account:" << msg.data.account << std::endl;
    out << "password:" << msg.data.password << std::endl;
    out << "book name:" << msg.data.book_name << std::endl;
    return out;
}


result::result()
{
    
}

void result::set_buffer(char buffer[BUFFER_SIZE])
{
    strcpy(_buffer, buffer);
}

void result::set_value(int value)
{
    _value = value;
}

int result::get_return_value()
{
    return _value;
}

char *result::get_return_buffer()
{
    return _buffer;
}