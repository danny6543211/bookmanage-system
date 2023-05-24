#include <client.hpp>

using namespace std;

int main()
{
    
    client client;
    
    client.send_message(LOG_IN, "danny456258", "da123456", "test_book");

    cout << "value: " << client.get_return_value() << "\n";
    cout << "buffer:\n" << client.get_return_buffer() << "\n";

    

}