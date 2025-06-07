#include <iostream>
#include <vector>
#include <string>

auto fn = [](const std::vector<std::string>& vec) -> std::vector<int> {
    std::vector<int> len;
    for (int i = 0; i < vec.size(); i++) {
        len.push_back(vec[i].length());
    }
    return len;
    };

int main() {
    std::vector<std::string> vec{ "BDHBSI", "shfijhiu", "hfuishui" };
    std::vector<int> len;
    len = fn(vec);
    for (int i = 0; i < len.size(); i++) {
        std::cout << len[i] << " ";
    }
    return 0;
}
