#include <client.hpp>
#include <vector>
#include <string>

using namespace std;

std::vector<std::string> bufferTrans(std::string str)
{
    std::vector<std::string> res;
    std::string::iterator it_l = str.begin();
    std::string::iterator it_r = str.begin();

    while (*it_r != '\0')
    {
        if (*it_r == '\n')
        {
            res.push_back(std::string(it_l, (it_r)));
            it_l = it_r+1;
        }
        it_r++;
    }

    return res;
}


int main()
{
    
    client client;
    
    client.send_message(SEARCH_BOOK, "danny456258", "da123456", "testBook1");

    auto buffer = bufferTrans(client.get_return_buffer());


}