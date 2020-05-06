#pragma once
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;
namespace Authenticate {
	string name;
	void inputUserName();
	string getUserName();
}
void Authenticate::inputUserName() {
start:
	cout << "Enter your username (8 letters only)" << endl;
	cin >> name;
	if (name.length() != 8) {
		goto start;
	}
	for (auto i : name) {
		if (!isalpha(i)) {
			goto start;
		}
	}
}
string Authenticate::getUserName() {
	return name;
}