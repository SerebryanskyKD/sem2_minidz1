#pragma once

#ifdef MINIHW_01_EXPORTS
#define HW_01_API __declspec(dllexport)
#else
#define MINIHW_01_API __declspec(dllimport)
#endif
#include <vector>

extern "C" MINIHW_01_API double dispersion(std::vector <float> numb);

extern "C" MINIHW_01_API double median(std::vector <float> numb);

extern "C" MINIHW_01_API double avgSqr(std::vector <float> numb);

extern "C" MINIHW_01_API double avgValue(std::vector <float> numb);