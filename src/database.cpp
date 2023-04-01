#include <iostream>
#include <string>
#include <sqlite3.h>
#include "database.h"

database::database() {}

database::~database()
{
    sqlite3_close(db);
}
