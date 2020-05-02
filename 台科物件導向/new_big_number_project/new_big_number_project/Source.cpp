#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <ctype.h>
//#define big_number_no_error_message//關閉錯誤訊息並繼續運行
#define big_number_error_keep_going//有錯誤訊息，印出後繼續運行
//如果上面兩個都沒有define，就會印出錯誤訊息，並終止印出。
#include "big_number.h"
using namespace std;
int main() {
	//big_number_add((string)"11.2222", (string)"3.32323").print();
	//return 0;
	string temp;
	system("title 大數計算機 支援小數，不支援除法  格式:  1+1 1-1  1*1 一次只能處理兩個數");
	while (/*cout << "a= ",*/getline(cin, temp)) {
		big_number a, b;
		//string_big_number_calculate(temp)[0].print();
		//a.input(temp);
		//cout << "b= ";
		//getline(cin, temp);
		//b.input(temp);
		//cout << "a+b = ";big_number_add(a, b).print();cout << '\n';
		//cout << "a-b = ";big_number_minus(a, b).print();cout << '\n';
		//cout << "a*b = ";big_number_multiply(a, b).print();cout <<"\n=========================\n";
		cout << "= ";big_number_formula(temp).print();cout << "\n=========================\n";
	}//231-321
	return 0;
}