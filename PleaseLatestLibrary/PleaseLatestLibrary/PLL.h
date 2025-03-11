#pragma once

#ifdef PLL_EXPORTS
#define PLL_API _declspec(dllexport)
#else
#define PLL_API _declspec(dllimport)
#endif

PLL_API float average_value(float a, float b, float c);
PLL_API float median(float a, float b, float c);
PLL_API float mean_square(float a, float b, float c);
PLL_API float number_series_variance(float a, float b, float c);