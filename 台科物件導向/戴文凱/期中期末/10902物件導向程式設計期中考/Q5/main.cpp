#include "BigInt.h"

#include <iostream>
using namespace std;

int main() {

	BigInt a;
	int b;

	while (cin >> a >> b) {
		a /= b;
		cout << a << endl;
	}

	return 0;
}