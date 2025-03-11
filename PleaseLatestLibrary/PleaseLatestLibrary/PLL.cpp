#include "PLL.h"
#include "pch.h"
#include <algorithm>

float average_value(float a, float b, float c)
{
    return (a + b + c) / 3;
}

float median(float a, float b, float c)
{
    float numbers[3] = { a, b, c };
    std::sort(numbers, numbers + 3);
    return numbers[1];
}

float mean_square(float a, float b, float c)
{
    float sum_squares = a*a + b*b + c*c;
    return sqrt(sum_squares / 3.0f);
}

float number_series_variance(float a, float b, float c)
{
    float mean = (a + b + c) / 3.0f;
    float sum_deviations = (a-mean) * (a-mean) + (b-mean) * (b-mean) + (c-mean) * (c-mean);
    return sum_deviations / 3.0f;
}