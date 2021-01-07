#include "llUtility.h"

std::string llUtility::to_string(int value) {
	std::string result{};
	while(value != 0){
		const char c = static_cast<char>((value % 10) + 48);
		result.insert(result.begin(), c);
		value /= 10;
	}
	return result;
}

std::string llUtility::to_string(double value, int accuracy) {
	if (accuracy < 0) {
		throw "accuracy cannot be less than 0";
	}
	std::string result1{};
	std::string result2{};
	int before{ static_cast<int>(value) };
	double after{value - before};
	result1.append(to_string(before));
	result2.push_back('.');
	while (after != 0.0 && accuracy > 0) {
		after *= 10;
		int i = static_cast<int>(after);
		const char c = static_cast<char>(i + 48);
		result2.insert(result2.end(), c);
		after -= i;
		--accuracy;
	}
	return result1.append(result2);
}

std::string llUtility::to_string(const std::string& value) {
	return value;
}