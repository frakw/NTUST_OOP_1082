#include <iostream>
#include <algorithm>
#include <string>
#include <ctype.h>
using namespace std;

typedef struct _Big_int {
	string num;
}big_int;

big_int Add(big_int&, big_int&);

int main() {
	int case_num;
	while (cin >> case_num) {
		for (int i = 0;i < case_num;i++) {
			big_int a;
			big_int b;
			bool not_num = false;
			cin >> a.num;
			cin >> b.num;
			for (int j = 0;j < a.num.length();j++) {
				if (!isdigit(a.num[j])) {
					not_num = true;
					break;
				}
			}
			for (int j = 0;j < b.num.length();j++) {
				if (!isdigit(b.num[j])) {
					not_num = true;
					break;
				}
			}
			if (not_num) {
				cout << "Not a valid number, please try again.\n";
			}
			else {
				cout << Add(a, b).num << endl;
			}
		}
	}
	return 0;
}

big_int Add(big_int& a, big_int& b) {
	int carry = 0;
	big_int result;
	if (a.num.length() < b.num.length()) {
		swap(a, b);
	}
	int len = (a.num.length() - b.num.length());
	for (int i = 0;i < len;i++) {
		b.num = (char)'0' + b.num;
	}
	for (int i = a.num.length() - 1;i >= 0;i--) {
		int add = (a.num[i] - '0') + (b.num[i] - '0') + carry;
		if (add > 9) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.num = (char)(add % 10 + '0') + result.num;
	}
	if (carry) {
		result.num = (char)'1' + result.num;
	}
	return result;
}