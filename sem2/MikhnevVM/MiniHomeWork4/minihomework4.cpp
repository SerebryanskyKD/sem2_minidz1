#include <vector>
#include <string>
#include <algorithm>

int main() {
    std::vector<std::string> strings = {"bananaman", "bananatup", "cherryman"};
    std::vector<size_t> charCounts(strings.size());
    
    // std::transform + лямбда
    std::transform(
        strings.begin(), strings.end(),  
        charCounts.begin(),             
        [](const std::string& str) {   
            return str.size();
        }
    );
    
    return 0;
}