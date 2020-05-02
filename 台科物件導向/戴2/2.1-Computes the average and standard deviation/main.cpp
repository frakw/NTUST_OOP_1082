#include <iostream>
#include <fstream>
#include <cmath>
using std::endl;
int main() {
	int i, casenum;
	while (!std::cin.eof()) {
		double sum = 0;
		std::cin >> casenum;
		double* arr = new double[casenum];
		for (i = 0; i < casenum; i++) {
			std::cin >> arr[i];
			sum += arr[i];
		}
		double averge = sum / (double)casenum;
		double up = 0;
		for (i = 0; i < casenum; i++) {
			up += pow(averge - arr[i], 2.0);
		}
		std::cout << "Average:" << averge << "	Standard deviation:" << sqrt(up / (double)casenum) << endl;
		//Average:4893.98	Standard deviation:3132.93
		delete[] arr;
	}
	return 0;
}