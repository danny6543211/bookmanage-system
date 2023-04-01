#include "user_manage.h"
#include <iostream>

int main()
{
    user_manage test;
    std::cout << test.log_in("merry", "ibi") << std::endl;

    return 0;
}
