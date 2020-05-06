#include <iostream>
#include <algorithm>
using namespace std;

int main() {
	int a, b;
	while (cin >> a) {
		int max = 0;
		cin >> b;
		int temp_a=a, temp_b=b;
		if (a > b) {
			temp_b = a;
			temp_a = b;
		}
		for (int i = temp_a;i <= temp_b;i++) {
			int temp = i;
			int count = 1;
			while (temp != 1) {
				if (temp % 2) {
					temp = temp*3+1;
				}
				else {
					temp /= 2;
				}
				count++;
			}
			if (count > max) {
				max = count;
			}
		}
		cout << a << " "<< b << " " << max<<endl;
	}
}