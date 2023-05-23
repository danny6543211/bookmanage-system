#include <client.hpp>

using namespace std;

int main()
{
    
    client client;
    
    // client.send_message(ADD_BOOK, "danny456258", "da123456", "test_book");
    // client.send_message(DELETE_BOOK, "danny456258", "da123456", "test_book");
    client.send_message(LOG_IN, "test_account", "test_password", "test_book");

    cout << "value: " << client.get_return_value() << "\n";
    cout << "buffer:\n" << client.get_return_buffer() << "\n";

    

}