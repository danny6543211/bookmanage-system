#include <iostream>
#include <string>
#include <chrono>
#include <cstring>
#include "include/sqlite3.h"
#include "include/message.h"

char buffer[BUFFER_SIZE];

std::string foo();

int main()
{
    std::cout << foo() << std::endl;
}

std::string foo()
{
    sqlite3 *db;
    sqlite3_open("user_libary.db", &db);

    std::string cmd = "select * from rent_book_table where account ==  'test_account';";

    char buffer[BUFFER_SIZE] = "";
    char *err;

    sqlite3_exec(db, cmd.c_str(), [](void *data, int argc, char **argv, char **colName)->int {
        strcat((char *)data, argv[0]);
        strcat((char *)data, " ");
        strcat((char *)data, argv[1]);
        strcat((char *)data, " ");
        strcat((char *)data, argv[2]);
        strcat((char *)data, "\n");
        return 0;
    }, buffer, &err);

    return buffer;
}