#pragma once

#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

class NumberGame {
public:

	ifstream fin;

	int A;
	vector<int> digits;
	map<int, int> numberList;
	map<int, int> validList;

	void Reset() {
		A = 0;
		validList.clear();
		numberList.clear();
		digits.clear();
		fin.close();
	}

	void SetInput(int input) {
		A = input;
	}

	void ProcessInput() {
		while (A > 0) {
			digits.push_back(A % 10);
			A /= 10;
		}
	}

	void SetFileName(std::string fileName) {
		fin.open(fileName);
	}

	void LoadNumberList() {
		int number;
		while (fin >> number) {
			numberList.insert(make_pair(number, number));
		}
	}

	void PrintAllValid() {
		for (int i = 1; i <= digits.size(); i++) {
			FindValid(i, 0, 1);
		}

		for (auto& v : validList) {
			cout << v.first << endl;
		}
	}

	void FindValid(int l, int idx, int product) {
		if (l == 0) {
			if (numberList.find(product) != numberList.end()) {
				validList[product] = product;
			}
			return;
		}
		else if (l > (digits.size() - idx)) {
			return;
		}

		for (int i = idx; i < digits.size(); i++) {
			FindValid(l - 1, i + 1, product * digits[i]);
		}
	}

};