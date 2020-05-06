#include "NumberGame.h"
void NumberGame::SetInput(int a) {//set the given integer A.
	input = a;
}
void NumberGame::ProcessInput() {//splitting the integer A into several digits.
	int len = to_string(input).length();
	int max_digit = pow(2.0, (double)len) ;
	for (int i = 1;i < max_digit;i++) {
		int sum=1;
		bitset<32> digit(i);
		for (int j = 0;j < len;j++) {
			if (digit[j]== 1) {
				sum *= (to_string(input)[j]-'0');
			}
		}
		valid.push_back(sum);
	}
}
void NumberGame::SetFileName(string a) {// set the file name of the file where list S is located.
	filename = a;
}
void NumberGame::LoadNumberList() {//read list S from the file.
	ifstream file(filename);
	int in;
	while (file >> in) {
		for (int i = 0;i < valid.size();i++) {
			if (in == valid[i]) {
				result.push_back(in);
				break;
			}
		}
	}
}
void NumberGame::PrintAllValid() {//print all the valid numbers in S ascendingly
	for (int i = 0;i < result.size();i++) {
		cout << result[i] << endl;;
	}
}
void NumberGame::Reset() { //reset all variables.
	result.clear();
	valid.clear();
	filename = "";
	input = 0;
}
