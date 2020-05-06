#include<iostream>
#include<cmath>
#include <iomanip>
#include <fstream>
using std::endl;
int main() {
	while (!std::cin.eof()) {
		double r, n, guess, previous = 0.0;
		std::cin >> n;
		guess = n / 2;
		while (fabs(guess - previous) > 0.01) {
			r = (n / guess);
			previous = guess;
			guess = (guess + r) / 2;
		}
		std::cout << std::fixed << std::setprecision(2) << guess << endl;
	}
	return 0;
}