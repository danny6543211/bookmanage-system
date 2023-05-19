#include <book_library.h>
#define SEARCH_BUFFER_SIZE 512

book_library::book_library() : database_base("book_database")
{
}

book_library::~book_library()
{
}

// 添加書
void book_library::add_book(std::string book_name)
{
    std::string sql_cmd("insert into books (book_name, status, position) values");
    sql_cmd += " ('" + book_name + "', 1, '1F');";

    char *err_msg;

    int res = sqlite3_exec(__db, sql_cmd.c_str(), nullptr, nullptr, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
}

// 查詢是否有書
int book_library::check_book(std::string book_name)
{
    std::string sql_cmd = "select * from books where book_name == '" + book_name + "';";

    int find = 0;
    char *err_msg;

    int res = sqlite3_exec(
        __db, sql_cmd.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(bool *)data = 1;
        return 0; },
        &find, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

    return find;
}

// 查詢書狀態 返回状态
int book_library::book_status(std::string book_name)
{
    std::string sql_cmd = "select status from books where book_name == '" + book_name + "';";

    int status = -1;
    char *err_msg;

    int res = sqlite3_exec(
        __db, sql_cmd.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(int *)data = std::stoi(argv[2]);
        return 0; },
        &status, &err_msg);
    
    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

    return status;
}

// 改變書狀態
void book_library::change_book_status(std::string book_name, int new_status)
{
    std::string sql_cmd = "update books set status = ";
    sql_cmd += std::to_string(new_status) + " where book_name = '" + book_name + "';";

    char *err_msg;
    
    int res = sqlite3_exec(__db, sql_cmd.c_str(), nullptr, nullptr, &err_msg);
    
    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

}

// 删除书
void book_library::delete_book(std::string book_name)
{
    std::string sql_cmd = "delete from books where book_name == '" + book_name + "';";

    char *err_msg;

    int res = sqlite3_exec(__db, sql_cmd.c_str(), nullptr, nullptr, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
}

// 透过字段查询有啥书
std::string book_library::search_book(std::string keyword)
{
std::string sql = "select * from books where book_name like '%";
    sql += keyword + "%';";

    char buffer[SEARCH_BUFFER_SIZE] = "";
    char *err_msg;
    
    int res = sqlite3_exec(__db, sql.c_str(), [](void *data, int colCount, char **colValue, char **colName) -> int
    {
        strcat((char *)data, colValue[0]);
        strcat((char *)data, "\n");

        strcat((char *)data, colValue[1]);
        strcat((char *)data, "\n");

        strcat((char *)data, colValue[2]);
        strcat((char *)data, "\n");

        strcat((char *)data, colValue[3]);
        strcat((char *)data, "\n");
    return 0; },
    buffer, &err_msg);
    // 結尾補\0
    buffer[strlen(buffer)] = '\0';
    
    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }   
    
    return std::string(buffer);
}

// 獲取book的ID
std::string book_library::get_book_id(std::string book_name)
{
    std::string sql_cmd = "select id from books where book_name = ";
    sql_cmd += "'" + book_name + "';";
    
    int id = -1;
    char *err_msg;
    
    int res = sqlite3_exec(__db, sql_cmd.c_str(), [](void *data, int colCount, char **colValue, char **colName) -> int
    {
        *(int*)data = atoi(colValue[0]);
    return 0; },
    &id, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    } 

    return std::to_string(id);
}
