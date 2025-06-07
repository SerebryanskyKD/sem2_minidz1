#include <iostream>
#include <vector>
#include <string>
#include <algorithm> 
#include <iterator>  

int main() {

    setlocale(LC_ALL, "Russian");

    std::system("cls");

    std::vector<std::string> string_vector = {
        "Проверка лямбда-выражения",
        "Оно должно вернуть 30 символов",
        "А здесь - 12",
        "1"
    };

    auto get_lengths_from_vector = [](const std::vector<std::string>& input_vec) -> std::vector<size_t> {

        std::vector<size_t> result_lengths;
        
        result_lengths.reserve(input_vec.size());

        std::transform(input_vec.begin(),input_vec.end(), 
            std::back_inserter(result_lengths), [](const std::string& s) {
                return s.length();     
            }
        );

        return result_lengths;
        };

    std::vector<size_t> lengths = get_lengths_from_vector(string_vector);

    std::cout << "Исходные строки и их длины:" << std::endl;
    for (size_t i = 0; i < string_vector.size(); ++i) {
        std::cout << "Строка: \"" << string_vector[i] << "\"" << std::endl;
        std::cout << "Длина: " << lengths[i] << " символов" << std::endl;
        std::cout << "---" << std::endl;
    }

    return 0;
}