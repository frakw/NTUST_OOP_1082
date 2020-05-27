#pragma once
template<typename T>
double absoluteValue(T a, T b) {
	if (a - b < 0) {
		return (a - b) * -1;
	}
	else {
		return (a - b);
	}
}