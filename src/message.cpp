#include <iostream>
#include "message.h"


std::ostream &operator<<(std::ostream &out, message &obj)
{
    using std::cout, std::endl;
    cout << "type:" << obj.type << endl;
    cout << "action" << obj.action << endl;
    cout << "data:" << "  account:" << obj.data.account 
                    << " password:" << obj.data.password
                    << "book name:" << obj.data.book_name
                    << endl;
}   