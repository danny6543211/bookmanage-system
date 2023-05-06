#include <chrono>
#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>

int main()
{




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