#pragma once
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;

namespace Authenticate {
string password;
extern void inputPassword() {
	start:
		while (1) {
			cout << "Enter your password (at least 8 characters and at least one non-letter)";
			cin >> password;
			if (password.length() < 8) {
				continue;
			}
			int non_letter_count = 0;
			for (auto i : password) {
				if (!isalpha(i)) {
					non_letter_count++;
				}
			}
			if (!non_letter_count) {
				goto start;
			}
		}
	}
	extern string getPassword() {
		return password;
	}
}