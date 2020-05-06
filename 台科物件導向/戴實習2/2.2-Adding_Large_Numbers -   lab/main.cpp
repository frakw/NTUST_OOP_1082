#include <iostream>
#include <algorithm>
#include <string>
#include <ctype.h>
using namespace std;

////typedef struct _big_number {
//	string num;
//}big_number;
class big_number {
public:
	big_number(std::string);
	big_number(bool sign,std::string);
	void print();
	void input(std::string);
	bool sign = true;
	string integer = "";
	string decimal = "";
};

big_number add(big_number,big_number);
big_number minus(big_number,big_number);
int main() {
	int case_num;
	while (cin >> case_num){
		for (int i = 0;i < case_num;i++) {
			big_number a;
			big_number b;
			bool not_num=false;
			cin >> a.integer;
			cin >> b.integer;
			for (int j = 0;j < a.integer.length();j++) {//絋粄Τ礚獶计じ
				if (!isdigit(a.integer[j])) {
					not_num = true;
					break;
				}
			}
			for (int j = 0;j < b.integer.length();j++) {//絋粄Τ礚獶计じ
				if (!isdigit(b.integer[j])) {
					not_num = true;
					break;
				}
			}
			if (not_num) {
				cout << "Not a valid number, please try again.\n";
			}
			else {
				cout << add(a, b).integer << endl;
			}
		}
	}
	return 0;
}

big_number add(big_number a, big_number b) {
	int carry=0;
	big_number result;
	if (a.integer.length() < b.integer.length()) {
		swap(a, b);//a祏b
	}
	int len= (a.integer.length() - b.integer.length());//a-b干箂计秖
	for (int i = 0;i < len;i++) {//干箂
		b.integer = "0" + b.integer;
	}
	for (int i = a.integer.length() - 1;i >=0;i--) {//眖计秨﹍
		int add = (a.integer[i] - '0') + (b.integer[i] - '0') + carry;
		if (add > 9) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.integer = (char)(add % 10 + '0') +result.integer;//癘眔璶锣char籔﹃
	}
	if (carry) {//矪瞶程秈
		result.integer = (char)'1' + result.integer;//癘眔璶锣char籔﹃
	}
	return result;
}
//#define minus
#ifdef minus
big_number minus(big_number& a, big_number& b) {
	int borrow = 0;
	big_number result;
	if (a.num.length() < b.num.length()) {
		swap(a, b);
	}
	else if (a.num.length() == b.num.length()) {
		int i;
		for (i = 0;i < a.num.length();i++) {
			if (a.num[i] < b.num[i]) {
				swap(a, b);
				break;
			}
		}
		if()
	}
	int len = (a.num.length() - b.num.length());
	for (int i = 0;i < len;i++) {
		b.num = "0" + b.num;
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
#endif