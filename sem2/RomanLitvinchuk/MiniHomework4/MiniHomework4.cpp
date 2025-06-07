#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> strings = { "behave", "word", "anything", "example" };

    auto getLengths = [](const std::vector<std::string>& vec) {
        std::vector<size_t> lengths;
        for (const auto& str : vec) {
            lengths.push_back(str.size());
        }
        return lengths;
        };
    std::vector<size_t> lengths = getLengths(strings);
    for (auto leng : lengths) 
    {
        std::cout << leng << std::endl;
    }

    return 0;
}
