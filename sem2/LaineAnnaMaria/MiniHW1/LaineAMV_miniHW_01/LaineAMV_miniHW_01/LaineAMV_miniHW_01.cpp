
#include <iostream>
#include <vector>
#include <HW_01.h>

int main()
{
    std::vector <float> arr = {7, 9, 0, 4};
    std::cout << dispersion(arr) << "\n";
    std::cout << median(arr) << "\n";
    std::cout << avgSqr(arr) << "\n";
    std::cout << avgValue(arr) << "\n";
}