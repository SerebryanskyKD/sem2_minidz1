#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    auto count_elements = [](const std::vector<std::string>& vec) {
        std::vector<int> lengths(vec.size());
        std::transform(vec.begin(), vec.end(), lengths.begin(), [](const std::string& elem) {
            return elem.length();
            });
        return lengths;
    };

    std::vector<std::string> vec = { "Hello", "world", "", "lol", "!"};
       
    for (auto elem : count_elements(vec))
    {
        std::cout << elem << std::endl;
    }
}

