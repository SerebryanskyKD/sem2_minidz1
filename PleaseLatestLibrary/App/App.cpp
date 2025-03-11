#include <iostream>
#include "PLL.h"

int main() {
    std::cout << "Введите 3 числа" << std::endl;
    float a, b, c;
    std::cin >> a >> b >> c;

    std::cout << "Среднее значение: " << average_value(a, b, c) << std::endl;
    std::cout << "Медиана: " << median(a, b, c) << std::endl;
    std::cout << "Среднее квадратическое: " << mean_square(a, b, c) << std::endl;
    std::cout << "Дисперсия числового ряда: " << number_series_variance(a, b, c) << std::endl;
    return 0;
}

//xcopy /y /d "..\..\PleaseLatestLibrary\x64\Debug$(IntDir)PleaseLatestLibrary.dll" "$(OutDir)"