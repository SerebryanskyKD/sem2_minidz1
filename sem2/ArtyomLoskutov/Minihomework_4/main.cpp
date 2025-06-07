#include <iostream>
#include <string>
#include <vector>

int main()
{
    std::vector<std::string> book{ "123", "abc" };

    auto len = [&book]()
        {
            for (std::string paper : book)
            {
                std::cout << paper.length();
            }
        };
}
