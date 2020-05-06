#pragma once
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;

namespace Authenticate {
	string password;
	void inputPassword();
	string getPassword();
}

void Authenticate::inputPassword() {
start:
	cout << "Enter your password (at least 8 characters and at least one non-letter)" << endl;
	cin >> password;
	if (password.length() < 8) {
		goto start;
	}
	int non_alpha_count = 0;
	for (auto i : password) {
		if (!isalpha(i)) {
			non_alpha_count++;
		}
	}
	if (!non_alpha_count) {
		goto start;
	}
}

string Authenticate::getPassword() {
	return password;
}