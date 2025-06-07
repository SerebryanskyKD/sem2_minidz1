#include <functional>
#include <iostream>
#include <vector>

int main() {
	std::vector<std::string> strings = { "I", "am", "love", "C++" };
	std::vector<size_t> sizes;

	std::transform(strings.begin(), strings.end(), std::back_inserter(sizes), [](const std::string& str) { return str.size(); });
	std::for_each(sizes.begin(), sizes.end(), [](const size_t& i) { std::cout << i << " "; });
}