#include <algorithm>
#include <vector>
#include <iostream>
#include <string>

int main() {
	std::vector<std::string> str = { "askjdn", "lqmk", "JNWDQKJNDQKJ" };

	auto len = [](const std::vector<std::string>& str) {
		std::vector<int> res;
		for (int i = 0; i < str.size(); i++) { res.push_back(str[i].length()); };
		return res;
	};

	//output
	const std::vector<int> res = len(str);
	for (int i = 0; i < res.size(); i++) { std::cout << res[i] << "\n"; };
};