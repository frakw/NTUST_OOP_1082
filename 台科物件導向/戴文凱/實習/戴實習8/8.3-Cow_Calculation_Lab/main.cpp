#include <iostream>
#include<string>
#include<cmath>
#include<algorithm>
using namespace std;
int to_number(string a);
int main() {
	int case_num;
	cin >> case_num;
	cin.ignore();
	cout << "COWCULATIONS OUTPUT" << endl;
	for (int i = 0;i < case_num;i++) {
		string input1;
		string input2;
		string result;
		int total = 0;		
		cin >> input1 >> input2;
		int num1 = to_number(input1), num2= to_number(input2);
		cin.ignore();
		for (int j = 0;j < 3;j++) {
			char op;
			cin >> op;
			switch (op){
			case'A':num2 = num1+num2;break;
			case'R':num2 /= 4;break;
			case'L':num2 *= 4;break;
			case'N':break;
			}
		}
		cin >> result;
		cout << ((to_number(result) == num2) ? "YES" : "NO")<<endl;
	}
	cout << "END OF OUTPUT" << endl;
    return 0;
}

int to_number(string a) {
	int result=0;
	for (int i = 0;i < a.length();i++) {
		switch (a[i]) {
		case'V': result = result * 4 + 0;break;
		case'U': result = result * 4 + 1;break;
		case'C': result = result * 4 + 2;break;
		case'D': result = result * 4 + 3;break;
		}
	}
	return result;
}
//ASDASASDAD
/*
5
VVVVU
VVVVU
A
A
A
VVVVVVUV
VVCCV
VVDCC
L
R
A
VVVVUCVC
VVCCV
VVDCC
R
L
A
VVVVUCVV
VVUUU
VVVVU
A
N
N
VVVVVUCU
DDDDD
VVVVU
A
L
L
UVVVVVVV

*/