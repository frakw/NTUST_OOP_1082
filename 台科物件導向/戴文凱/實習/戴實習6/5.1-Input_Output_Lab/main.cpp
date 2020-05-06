#include <iostream>
#include <string>
#include <sstream>
using namespace std;

int main() {
	string input;
	while (getline(cin,input)) {
		string number;
		int total_len;
		int decimal_len;
		char trash,others;
		stringstream(input)>> number >> total_len >> decimal_len;
		others = input[input.length() - 1];
		//cout << number << endl << total_len << endl << decimal_len << endl << others << endl;
		
		int dot_pos = number.length();
		for (int i = 0;i < number.length();i++) {
			if (number[i] == '.') {
				dot_pos = i;
				break;
			}
		}
		int pre_dot_len = total_len - decimal_len - (decimal_len!=0?1:0);
		for (int i = 0;i < (pre_dot_len-dot_pos);i++) {
			cout << others;
		}
		for (int i = 0;i < dot_pos;i++) {
			cout << number[i];
		}
		cout << (string)(decimal_len != 0 ? "." : "");
		for (int i = 0;i<decimal_len;i++) {
			if ((i + dot_pos + 1) >= number.length()) {
				cout << 0;
			}
			else {
				cout << number[i + dot_pos + 1];
			}
		}
		cout << endl;
	}
    return 0;
}