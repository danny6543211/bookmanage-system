#include <iostream>
#include "sqlite_api.h"

int main()
{
    data_base db(USERS_TABLE);
    db.add_user("test", 123456);
    db.add_user("test", 123456);

    return 0;
}