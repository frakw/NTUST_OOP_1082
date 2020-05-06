#pragma once
#include<iostream>
#include<string>
#include<ctype.h>
using namespace std;
namespace Authenticate {
	string name;
	extern void inputUserName() {
	start:
		cout << "Enter your username (8 letters only)";
		while(1){
			cin >> name;
			if (name.length() < 8) {
				continue;
			}
			for (auto i : name) {
				if (!islower(i)) {
					goto start;
				}
			}
		}
	}
	extern string getUserName() {
		return name;
	}
}