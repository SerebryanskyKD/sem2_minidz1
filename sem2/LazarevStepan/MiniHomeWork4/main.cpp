#include <iostream>
#include <string>
#include <sstream>
#include <functional>
#include <vector>

int main(){
    auto countWords = [](const std::string& str) {
        std::vector<int> counts;
        std::istringstream iss(str);
        std::string line;

        int count = 0;
        while (std::getline(iss, line))
        {
            std::istringstream words(line);
            std::string word;
            int count = 0;
            while (words >> word) ++count;
            counts.push_back(count);
        }
        return counts;
    };

    std::string text = "hello!\n are you listening?\n it's me!\n Mario Petrovich!";
    std::vector<int> result = countWords(text);

    for (size_t i = 0; i < result.size(); ++i)
    {
        std::cout << "Line: " << i << ", words: " << result.at(i) << std::endl;
    }

    return 0;
}