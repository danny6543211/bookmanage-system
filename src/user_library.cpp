#include <string>
#include <chrono>
#include <user_library.h>
#include <book_library.h>
#define RENT_BOOK_BUFFER_SIZE 512

user_library::user_library() : database_base("user_database")
{
}

user_library::~user_library()
{
}

void user_library::add_user(std::string account, std::string password)
{

    std::string sql_command = "insert into user_info (account,password,permission) values";
    sql_command += " ('" + account + "','" + password + "', 1);";

    char *err_msg;

    int res = sqlite3_exec(__db, sql_command.c_str(), nullptr, nullptr, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
}

int user_library::check_user(std::string account)
{
    std::string sql_cmd = "select * from user_info where account == '" + account + "';";

    int find = 0;
    char *err_msg;

    int res = sqlite3_exec(
        __db, sql_cmd.c_str(),
        [](void *data, int argc, char **argv, char **colName) -> int
        {
            // 有数据把find改成1
            *(int *)data = 1;
            return 0;
        },
        &find, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

    return find;
}

int user_library::check_user(std::string account, std::string password)
{
    std::string sql_cmd = "select * from user_info where account == '" + account + "'";
    sql_cmd += " and password == '" + password + "';";

    int find = 0;
    char *err_msg;

    int res = sqlite3_exec(
        __db, sql_cmd.c_str(),
        [](void *data, int argc, char **argv, char **colName) -> int
        {
            // 有数据把find改成1
            *(int *)data = 1;
            return 0;
        },
        &find, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

    return find;
}

void user_library::add_rent_book(std::string account, std::string book_name)
{
    // 獲取當前日期時間
    auto now = std::chrono::system_clock::now();
    time_t time = std::chrono::system_clock::to_time_t(now);
    // 借书日期为三个月
    time_t return_date = time + 2592000;

    std::string c_date = ctime(&time);
    std::string r_date = ctime(&return_date);
    *(c_date.rbegin()) = ' ';
    *(r_date.rbegin()) = ' ';

    std::string sql_cmd = "insert into rent_book_table (account, book_id,  book_name, date, return_date) values";
    sql_cmd += " ('" + account + "','" + get_book_id(book_name) + "','" + book_name + "', '" + c_date + "','" + r_date + "');";

    char *err_msg;

    int res = sqlite3_exec(__db, sql_cmd.c_str(), nullptr, nullptr, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
}

void user_library::delete_rent_book(std::string book_name)
{
    std::string sql_cmd = "delete from rent_book_table where book_name == ";
    sql_cmd += "'" + book_name + "';";

    char *err_msg;

    int res = sqlite3_exec(__db, sql_cmd.c_str(), nullptr, nullptr, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
}

std::string user_library::get_my_rent_book(std::string account)
{
    std::string sql_cmd = "select * from rent_book_table where account == ";
    sql_cmd += "'" + account + "';";

    char *err_msg;
    char buffer[RENT_BOOK_BUFFER_SIZE] = "";

    // 返回借書數據
    int res = sqlite3_exec(
        __db, sql_cmd.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        // 编号
        // strcat((char *)data, this->get_book_id(account).c_str());
        // strcat((char *)data, " ");
        // 书名
        strcat((char *)data, argv[1]);
        strcat((char *)data, "\n");
        // 借书日期
        strcat((char *)data, argv[2]);
        strcat((char *)data, "\n");
        
        strcat((char *)data, argv[3]);
        strcat((char *)data, "\n");

        strcat((char *)data, argv[4]);
        strcat((char *)data, "\n");

        return 0; },
        buffer, &err_msg);

    buffer[strlen(buffer)] = '\0';

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }

    return std::string(buffer);
}

int user_library::get_type(std::string account)
{
    std::string sql_command = "select * from user_info where account == '" + account + "';";
    
    char *err_msg;
    // -1表示沒有此帳戶
    int type = -1;
    
    int res = sqlite3_exec(
        __db, sql_command.c_str(), [](void *data, int argc, char **argv, char **colName) -> int
        {
        *(int *)data = std::stoi(std::string(argv[3]).c_str());
        return 0; },
        &type, &err_msg);

    if (res != SQLITE_OK)
    {
        // 錯誤寫進日誌
        Logger database_log("./log/log.txt");
        database_log.Log(LogLevel::ERROR, err_msg);
    }
    
    return type;
}

std::string user_library::get_book_id(std::string book_name)
{
    book_library book_library;
    return book_library.get_book_id(book_name);
}
