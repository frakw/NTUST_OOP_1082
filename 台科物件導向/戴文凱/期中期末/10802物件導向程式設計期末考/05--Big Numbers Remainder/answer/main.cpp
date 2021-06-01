#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> split(string src)
{
	vector<string> tokens;
	string token = "";
	for (char c : src) {
		if ((c == ' ' || c == '\t')) {
			if (!token.empty()) {
				tokens.push_back(token);
				token.clear();
			}
		}
		else {
			token += c;
		}
	}

	if (!token.empty())
		tokens.push_back(token);

	return tokens;
}

bool checkValidNumber(string src)
{
	for (int i = 0; i < src.size(); i++) {
		if (!i && src[i] == '-' && src.size() != 1)
			continue;
		if (!isdigit(src[i]))
			return false;
	}

	if (src == "-0")
		return false;

	return true;
}

bool checkValid(vector<string> src)
{
	if (src.size() != 2)
		return false;

	for (int i = 0; i < src.size(); i++) {
		if (!checkValidNumber(src[i]))
			return false;
	}

	return true;
}

string dzero(string src)
{
	int index;
	for (index = 0; index < src.size(); index++) {
		if (src[index] != '0')
			break;
	}

	if (index == src.size())
		return "0";

	src.erase(0, index);
	return src;
}

bool judge(string a, string b)
{
	if (a.size() > b.size())
		return true;
	else if (a.size() == b.size())
		return a >= b;
	else
		return false;
}

string diff(string a, string b)
{
	reverse(a.begin(), a.end());
	reverse(b.begin(), b.end());
	for (int i = 0; i < b.size(); i++)
		a[i] = a[i] - b[i] + '0';

	for (int i = 0; i < a.size(); i++) {
		if (a[i] < '0') {
			a[i] += 10;
			a[i + 1]--;
		}
	}
	reverse(a.begin(), a.end());
	return dzero(a);
}

string mod(string a, string b, bool checkMinus1, bool checkMinus2)
{
	if (judge(a, b)) {
		while (judge(a, b)) {
			int split = b.size();
			string part = a.substr(0, split);
			if (!judge(part, b))
				split += 1;
			part = a.substr(0, split);

			while (judge(part, b)) {
				part = diff(part, b);
			}
			a = dzero(part + a.substr(split, a.size()));
		}

		if (checkMinus1 && a != "0")
			a = '-' + a;
		return a;
	}
	else {
		if (checkMinus1 && a != "0")
			return '-' + a;
		else
			return a;
	}
}

int main() {
	string input;
	while (getline(cin, input))
	{
		vector<string> tokens = split(input);
		if (checkValid(tokens)) {
			bool checkMinus1 = tokens[0][0] == '-';
			bool checkMinus2 = tokens[1][0] == '-';
			if (checkMinus1)
				tokens[0].erase(tokens[0].begin());
			if (checkMinus2)
				tokens[1].erase(tokens[1].begin());

			cout << mod(tokens[0], tokens[1], checkMinus1, checkMinus2) << endl;
		}
		else {
			cout << "Input Error" << endl;
		}

	}
	return 0;
}