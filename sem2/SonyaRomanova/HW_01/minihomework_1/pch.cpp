﻿// pch.cpp: файл исходного кода, соответствующий предварительно скомпилированному заголовочному файлу

#include "pch.h"


float average_arithmetic(std::vector <float> x) {
	int i = 0;
	float s = 0; //сумма
	float a = 0; //среднее арифметическое 
	for (i; i < x.size(); i++) {
		s += x[i];
	}
	a = s / x.size();
	return a;
}



// При использовании предварительно скомпилированных заголовочных файлов необходим следующий файл исходного кода для выполнения сборки.
