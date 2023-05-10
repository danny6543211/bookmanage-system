#include <chrono>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include "sqlite3.h"

int main()
{

    sqlite3 *db;
    sqlite3_open("book_libary.db", &db);

    int id = -1;
    std::string sql = "select id from books where book_name = ";
    sql += "'test_book1';";
    char *err_msg;
    int res = sqlite3_exec(db, sql.c_str(), [](void *data, int colCount, char **colValue, char **colName) -> int
    {
        *(int*)data = atoi(colValue[0]);
    return 0; },
    &id, &err_msg);

    std::cout << id << std::endl;

}