#include <iostream>
#include <string>
#include <cmath>
using namespace std;

class Atoi {
private:
	string beTrans;
	char sign;
public:
	Atoi() {
		beTrans = "";
		sign = '\0';

	}
	Atoi(string s) {
		if (s[0] == '-') {
			sign = '-';
			s.erase(0, 1);
		}
		else {
			sign = '\0';
		}
		beTrans = s;
	}

	void SetString(string s) {
		if (s[0] == '-') {
			sign = '-';
			s.erase(0, 1);
		}
		else {
			sign = '\0';
		}
		beTrans = s;
	}

	const string GetString() {
		return beTrans;
	}

	int Length() {
		return beTrans.length();
	}

	bool IsDigital() {
		int length = this->Length();

		for (int i = 0; i < length; i++) {
			if (!isdigit(beTrans[i])) {
				cout << "Isn't digital." << endl;
				return false;
			}
		}
		
		return true;
	}

	int StringToInteger() {
		int digital = 0;

		if (this->IsDigital()) {
			int length = this->Length();
			for (int i = 0; i < length; i++) {
				i == 0? digital += (beTrans[length - i - 1] - '0') : digital += (beTrans[length-i-1] - '0') * pow(10, i);
			}
			if (sign == '-') {
				digital *= -1;
			}
		}

		return digital;
	}

};

int main(void) {
	string beTrans;
	
	while (cin >> beTrans) {
		Atoi atoi(beTrans+"20");
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}

		atoi.SetString(beTrans);
		if (atoi.IsDigital()) {
			cout << atoi.Length() << endl;
			cout << atoi.StringToInteger() << endl;
			cout << sizeof(atoi.StringToInteger()) << endl;
		}
	}

	return 0;
}