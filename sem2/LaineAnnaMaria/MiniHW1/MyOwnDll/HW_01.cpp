#include "pch.h"

#include "HW_01.h"

double dispersion(std::vector <float> numb) {
	double sum = 0, res = 0, avg;
	if (numb.size() != 0) {
		for (int i = 0; i < numb.size(); i++) {
			sum += numb[i];
		}
		avg = sum / numb.size();
		std::vector <float> sqrDev;
		for (int i = 0; i < numb.size(); i++) {
			sqrDev.push_back(pow(numb[i] - avg, 2));
		}
		sum = 0;
		for (int i = 0; i < sqrDev.size(); i++) {
			sum += sqrDev[i];
		}
		res = sum / sqrDev.size();
	}
	return res;
}

double median(std::vector <float> numb) {
	double res = 0;
	if (numb.size() == 0) {
		return 0;
	}
	else if (numb.size() % 2 == 0) {
		return (numb[numb.size() / 2] + numb[(numb.size() / 2) - 1]) / 2;
	}
	else {
		return numb[floor(numb.size() / 2)];
	}
}
double avgSqr(std::vector <float> numb) {
	double sum = 0, res = 0;
	if (numb.size() != 0) {
		for (int i = 0; i < numb.size(); i++) {
			sum += pow(numb[i],2);
		}
		res = sqrt(sum / numb.size());
	}
	return res;
}

double avgValue(std::vector <float> numb) {
	double sum = 0, res = 0;
	if (numb.size() != 0) {
		for (int i = 0; i < numb.size(); i++) {
			sum += numb[i];
		}
		res = sum / numb.size();
	}
	return res;
}
