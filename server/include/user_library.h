#ifndef USER_LIBRARY_H
#define USER_LIBRARY_H
#include <string>
#include <cstring>
#include <database_base.hpp>

class user_library : private database_base 
{
public:
    user_library();

    ~user_library();
    
    // 添加帳戶     
    void add_user(std::string account, std::string password);

    // 查巡是否有帳號
    int check_user(std::string account);
    
    // 查詢是否有帳號加密碼       
    int check_user(std::string account, std::string password);
    
    // 使用者增加借书数据     
    void add_rent_book(std::string account, std::string book_name);
    
    // 删除借书数据        
    void delete_rent_book(std::string book_name);
    
    // 查看借書表
    std::string get_my_rent_book(std::string account);

    // 查看user類型
    int get_type(std::string account);

private:
    // 獲取圖書ID
    std::string get_book_id(std::string book_name);
    
};


#endif