#include <chrono>
#include <iostream>
#include <cstring>
#include <vector>

std::vector<std::string> foo(std::string str);

int main()
{
    std::string buffer = "test_book1\nSat May 06 14:59:47 2023 \nMon Jun 05 14:59:47 2023\n";

    std::vector<std::string> res = foo(buffer);

    for (std::vector<std::string>::iterator it = res.begin(); it != res.end(); it++)
    {
        std::cout << *it;
    }

}

std::vector<std::string> foo(std::string str)
{
    std::vector<std::string> res;
    std::string::iterator it_l = str.begin();
    std::string::iterator it_r = str.begin();

    while (it_r != str.end())
    {
        if (*it_r == '\n')
        {
            res.push_back(std::string(it_l, it_r));
            it_l = it_r;
        }
        it_r++;
    }

    return res;
}