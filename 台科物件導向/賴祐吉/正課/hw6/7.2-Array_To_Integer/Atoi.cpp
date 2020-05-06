/*
	Atoi();
	Atoi(string s);
	void SetString(string s);
	const string GetString();
	int Length();
	bool IsDigital();
	int StringToInteger();
*/
#include "Atoi.h"

Atoi::Atoi() {
	beTrans = "";
}

Atoi::Atoi(string s) {
	beTrans = s;
}
void Atoi::SetString(string s) {
	beTrans = s;
}
const string Atoi::GetString() {
	return beTrans;
}
int Atoi::Length() {
	if (beTrans[0] == '-') {
	return beTrans.length()-1;
	}
	return beTrans.length();
}
bool Atoi::IsDigital() {
	if (beTrans.length() == 0) {
		return false;
	}
	if (!isdigit(beTrans[0])) {
		if (!(beTrans[0] == '-' && beTrans.length() != 1)) return false;
	}
	for (int i = 1;i < beTrans.length();i++) {
		if (!isdigit(beTrans[i])) {
			return false;
		}
	}
	return true;
}

int Atoi::StringToInteger() {
	if (beTrans.length() == 0) {
		return 0;
	}
	bool negative = beTrans[0] == '-';
	int result = 0;
	int end = beTrans[0] == '-' ? 1 : 0;
	for (int i = beTrans.length() - 1,j = 0;i >= end;i--,j++) {
		result += ((beTrans[i] - '0') * pow(10,j));
	}
	if (negative) {
		result *= -1;
	}
	return result;
}
/*
05
11
23
-10
-11
8946
1891231

*/