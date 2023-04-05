#include "message.h"

std::ostream &operator <<(std::ostream &out, message &msg)
{
    out << "type:" << msg.type << std::endl;
    out << "action:" << msg.action << std::endl;
    out << "account:" << msg.data.account << std::endl;
    out << "password:" << msg.data.password << std::endl;
    out << "book name:" << msg.data.book_name << std::endl;
}