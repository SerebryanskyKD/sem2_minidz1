#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>
#include <string>




int main()
{
    int n;
    std::cout << "Write the number of lines\n";
    std::cin >> n;
    std::cin.ignore();

    std::vector<std::string> lines(n);

    for (int i = 0; i < n; i++)
        std::getline(std::cin, lines[i]);

    std::for_each(lines.begin(), lines.end(), [](const std::string& str){
        std::cout << "Line \"" << str << "\" has " << str.length() << " symbols\n";
    });
}

