#include <iostream>
#include <cmath>
using namespace std;
int main() {
	int year;
	while (cin >> year) {
		unsigned long long int bit =4.0 * pow(2.0, (year - 1900)/10);
		long double temp = 0;
		for (int i = 2;;i++) {
			temp += log2(i);
			if (temp > bit){
				cout << i-1 <<endl;
				break;
			}
		}
	}
    return 0;
}

