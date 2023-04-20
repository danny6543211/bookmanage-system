#include <iostream>
#include "include/message.h"
#include "include/client_socket.h"
#include "include/sqlite3.h"
#include <cstdio>
#include <fstream>
using namespace std;

static int callback(void *data, int argc, char **argv, char **colName)
{
    
    for (int i = 0; i < argc-1; i++)
    {
        strcat((char *)data, argv[i]);
        strcat((char *)data, " ");
    }
    return 0;
}

int main()
{
    sqlite3 *db;
    sqlite3_open("user_libary.db", &db);
    char buffer[100] = "";
    sqlite3_exec(db, "select * from rent_book_table;", callback, buffer, nullptr);
    cout << buffer << endl;

    sqlite3_close(db);
}