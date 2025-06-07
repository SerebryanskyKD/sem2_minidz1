#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main() {
	std::vector<std::string> tommycash = { "Mi amore", "Mi amore", "Espresso", "Macchiato", "Macchiato", "Macchiato", "Por favore" };
	std::vector<size_t> l(tommycash.size());
	auto count = [](const std::string& str) {
		return str.size();
		};
	std::transform(tommycash.begin(), tommycash.end(), l.begin(), count);
	for (size_t i = 0; i < tommycash.size(); ++i) {
		std::cout << tommycash[i] << " " << l[i] << std::endl;
	}
}