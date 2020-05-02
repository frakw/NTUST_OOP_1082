#include "big_number.h"
#include <string>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <ctype.h>
#include <iostream>
#define isoperator(x) ((x)=='+' || (x)=='-' || (x)=='*' || (x)=='/')
#define issign(x) ((x)=='+' || (x)=='-')
big_number big_number_add(big_number a,big_number b) {//肚タ璽┪璽タㄤ穦笆だ瑈搭猭
	int carry = 0;
	big_number result;
	if (a.sign != b.sign) {
		if (a.sign) {//タ计璽计=タ搭璽
			b.sign = true;
			return big_number_minus(a, b);
		}
		else {
			a.sign = true;
			return big_number_minus(b, a);
		}
	}
	else if (!a.sign) {//璽计璽计タ盽猭秈︽程璽腹
		result.sign = false;
	}

	if (a.decimal.length() < b.decimal.length()) {
		std::string temp = a.decimal;
		a.decimal = b.decimal;
		b.decimal = temp;
	}
	if (a.integer.length() < b.integer.length()) {
		std::string temp = a.integer;
		a.integer = b.integer;
		b.integer = temp;
	}
	int decimal_zero_len = (a.decimal.length() - b.decimal.length());
	int integer_zero_len = (a.integer.length() - b.integer.length());
	for (int i = 0;i < decimal_zero_len;i++) {
		b.decimal = b.decimal + "0";
	}
	for (int i = 0;i < integer_zero_len;i++) {
		b.integer = "0" + b.integer;
	}
	for (int i = a.decimal.length() - 1;i >= 0;i--) {
		int add = (a.decimal[i] - '0') + (b.decimal[i] - '0') + carry;
		if (add > 9) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.decimal = (char)(add % 10 + '0') + result.decimal;
	}
	for (int i = a.integer.length() - 1;i >= 0;i--) {
		int add = (a.integer[i] - '0') + (b.integer[i] - '0') + carry;
		if (add > 9) {
			carry = 1;
		}
		else {
			carry = 0;
		}
		result.integer = (char)(add % 10 + '0') + result.integer;
	}
	if (carry) {
		result.integer = (char)'1' + result.integer;
	}
	for (int i = result.decimal.length() - 1;i >=0;i--) {//埃计翴程箂
		if (result.decimal[i] == '0') {
			result.decimal.pop_back();
		}
		else {
			break;
		}
	}
	return result;
}

big_number big_number_minus(big_number a, big_number b) {//肚タタ タ盽笲 璽璽 把计は患癹ㄤ穦笆だ瑈猭
	big_number result;
	int borrow = 0;//
	if (a.sign!=b.sign){//タ搭璽 璽搭タ ユ倒猭
		if (b.sign) {
			b.sign = false;
		}
		else {
			b.sign = true;
		}
		return big_number_add(a, b);
	}
	else if (!a.sign) {
		a.sign = true;
		b.sign = true;
		return big_number_minus(b,a);//璽璽 把计は患癹
	}
	switch (big_number_compare(a, b)) {
	case  0: {
		result.integer.push_back('0');//璶ノpush_back ぃノinteger[0] = '0'
		return result;
		break;
	}
	case -1: {
		result.sign = false;//璽计
		std::swap(a, b);//a
		break;
	}
	default:;
	}
	int integer_zero_len = (a.integer.length() - b.integer.length());//俱计璶干箂计秖
	int decimal_zero_len;//计璶干箂计秖
	int integer_max_len = a.integer.length() -1;//俱计程蔼计秖
	int decimal_max_len;//计程蔼计秖
	for (int i = 0;i < integer_zero_len;i++) {//俱计干箂
		b.integer = "0" + b.integer;
	}
	if (a.decimal.length() > b.decimal.length()) {
		decimal_zero_len = (a.decimal.length() - b.decimal.length());
		for (int i = 0;i < decimal_zero_len;i++) {//计干箂
			b.decimal.push_back('0');
		}
		decimal_max_len = a.decimal.length() - 1;
	}
	else {
		decimal_zero_len = (b.decimal.length() - a.decimal.length());
		for (int i = 0;i < decimal_zero_len;i++) {//计干箂
			a.decimal.push_back('0');
		}
		decimal_max_len = b.decimal.length() - 1;
	}
	for (int i = decimal_max_len;i >= 0;i--) {
		int minus = (a.decimal[i] - '0') - (b.decimal[i] - '0') + borrow;
		if (minus < 0) {
			borrow = -1;//
			minus += 10;
		}
		else {
			borrow = 0;
		}
		result.decimal = (char)(minus + '0') + result.decimal;
	}
	for (int i = integer_max_len;i >= 0;i--) {
		int minus = (a.integer[i] - '0') - (b.integer[i] - '0') + borrow;
		if (minus < 0) {
			borrow = -1;//
			minus += 10;
		}
		else {
			borrow = 0;
		}
		result.integer = (char)(minus + '0') + result.integer;
	}
	result.clear_zero();//睲埃俱计程玡0 籔计翴程0
	return result;
}

big_number big_number_multiply(big_number a, big_number b) {//猭
	big_number result;
	int carry = 0;
	int decimal_len = a.decimal.length() + b.decimal.length();
	std::string all_number_a = a.integer + a.decimal;
	std::string all_number_b = b.integer + b.decimal;
	int max_len = all_number_a.length() + all_number_b.length();
	int* all_result_number = new int[max_len]{};//珹腹﹍て场0ゼdelete
	if (a.sign != b.sign) {//タ璽 or 璽タ 眔璽
		result.sign = false;
	}
	int g = 0;
	for (int i = all_number_a.length() -1,k = max_len - 1;i >=0;i--,k--) {
		g = k;
		for (int j = all_number_b.length()-1;j >=0;j--,g--) {
			int multiply = (all_number_a[i] - '0') * (all_number_b[j] - '0') + carry;
			carry = multiply / 10;
			all_result_number[g] += (multiply%10);
		}
		all_result_number[g] += carry;
		carry = 0;
	}
	for (int i = max_len-1 ;i >= (max_len-decimal_len);i--) {//矪瞶秈肚result
		if (all_result_number[i] > 9) {
			all_result_number[i - 1] += (all_result_number[i] / 10);
			all_result_number[i] %= 10;
		}
		result.decimal = (char)(all_result_number[i]+'0') + result.decimal;
	}
	for (int i = (max_len - decimal_len - 1);i >= 0;i--) {
		if (all_result_number[i] > 9) {
			all_result_number[i - 1] += (all_result_number[i] / 10);
			all_result_number[i] %= 10;
		}
		result.integer = (char)(all_result_number[i]+'0') + result.integer;
	}
	result.clear_zero();//睲埃俱计程玡0 籔计翴程0
	delete[] all_result_number;
	return result;
}

int big_number_compare(big_number a, big_number b) {//a>b ->1   a==b ->0    a<b ->-1
	a.clear_zero();
	b.clear_zero();
	if (a.sign != b.sign) {
		if (a.sign) {
			return 1;
		}
		else {
			return -1;
		}
	}
	if (a.integer.length() > b.integer.length()) {
		return a.sign ? 1 : -1;
	}
	else if (a.integer.length() < b.integer.length()) {
		return a.sign ? -1 : 1;
	}
	else {//俱计
		for (int i = 0;i < a.integer.length();i++) {//ゑ俱计
			if (a.integer[i] > b.integer[i]) {
				return a.sign ? 1 : -1;
			}
			else if (a.integer[i] < b.integer[i]) {
				return a.sign ? -1 : 1;
			}
		}
		int decimal_little_len = (a.decimal.length() > b.decimal.length()) ? b.decimal.length() : a.decimal.length();
		for (int i = 0;i < decimal_little_len;i++) {//ゑ计
			if (a.decimal[i] > b.decimal[i]) {
				return a.sign ? 1 : -1;
			}
			else if (a.decimal[i] < b.decimal[i]) {
				return a.sign ? -1 : 1;
			}
		}
		if (a.decimal.length() > b.decimal.length()) {
			return a.sign ? 1 : -1;
		}
		else if(a.decimal.length() < b.decimal.length()){
			return a.sign ? -1 : 1;
		}
		else {
			return 0;
		}
	}
	return 0;//场
}
int big_number_compare(std::string a,std::string b) {//a>b ->1   a==b ->0    a<b ->-1
	big_number x;
	big_number y;
	x.input(a);
	y.input(b);
	return big_number_compare(x,y);
}

big_number::big_number(std::string input_s) {//旧input function
	input(input_s);
}


big_number::big_number() {
	clear();
}


void big_number::input(std::string input_s) {
	if (!input_s.length()) {
		integer.push_back('0');
		return;
	}
	integer.clear();
	decimal.clear();
	int i = 0;
	bool got_dot = false;
	for (int i = 0;i < input_s.length();i++) {//筁耾疭じ
		if(!(isdigit(input_s[i]) || input_s[i]==' ' || input_s[i] == '-' || input_s[i] == '+' || input_s[i] == '.' || input_s[i] == '\n')){
			fprintf(stderr, "this is not a standard number ! ! !\n");
			return;
		}
	}
	while (!isdigit(input_s[i])) {
		while (input_s[i] == ' ' && i < input_s.length()) { i++; }//菠筁玡よ
		while ((input_s[i] == '-' || input_s[i] == '+') && i < input_s.length()) { //矪瞶璽腹璽璽眔タ
			if (input_s[i] == '-') sign = !sign;
			i++;
		}
		if (input_s[i] == '.' && i < input_s.length()) {//Τ计翴计
			goto start;
		}
	}
	while (input_s[i] == '0' && i < input_s.length()) { i++; }//菠筁程玡箂
	start:
	for (;i < input_s.length();i++) {
		if (isdigit(input_s[i])) {
			if (got_dot) {
				decimal.push_back(input_s[i]);
			}
			else {
				integer.push_back(input_s[i]);
			}
		}
		else if (input_s[i] == '.' && !got_dot) {
			got_dot = true;
		}
		else {
			return;
		}
	}
	this->clear_zero();
}
bool clear_unknown(std::string* input) {
	bool error_occured = false;
	for (int i = 0;i < input->length();i++) {//筁耾ぃじ
		if (isdigit((*input)[i]) || (*input)[i] == '.' || (*input)[i] == '+' || (*input)[i] == '-' || (*input)[i] == '*' || (*input)[i] == '/' || (*input)[i] == '!' || (*input)[i] == '(' || (*input)[i] == ')') {

		}
		else if ((*input)[i] == ' ') {
			input->erase(input->begin() + i);
			i--;
			continue;
		}
		else if ((*input)[i] == '\n') {
			input->erase(input->begin() + i,input->end());
			break;
		}
		else {
			if (!error_occured) {
				fprintf(stderr, "format error! unknown character has been ignored.\nresult after ignored:");
			}
			input->erase(input->begin() + i);
			i--;
			error_occured = true;
			continue;
		}
	}
	return error_occured;
}
big_number big_number_formula(std::string input) {
	big_number a, b;
	std::string a_str, b_str;
	bool got_first_num = false;
	bool got_first_dot = false;
	bool got_second_num = false;
	bool got_second_dot = false;
	bool got_op = false;
	bool got_first_sign = false;
	bool got_second_sign = false;
	char op = '+';
	bool error_occured = clear_unknown(&input);;
	for (int i = 0;i < input.length();i++) {
		if (!got_first_num && issign(input[i])) {
			got_first_sign = true;
			a_str.push_back(input[i]);
		}
		else if ((isdigit(input[i]) || (!got_first_dot && input[i] == '.')) && !got_op) {
			if (isdigit(input[i])) {
				got_first_num = true;
			}
			else {
				got_first_dot = true;
			}
			a_str.push_back(input[i]);
		}
		else if (!got_op && got_first_num && isoperator(input[i])) {
			got_op = true;
			op = input[i];
		}
		else if (!got_second_num && issign(input[i]) && got_op) {
			got_second_sign = true;
			b_str.push_back(input[i]);
		}
		else if ((isdigit(input[i]) || (!got_second_dot && input[i] == '.')) && got_op) {
			if (isdigit(input[i])) {
				got_second_num = true;
			}
			else {
				got_second_dot = true;
			}
			b_str.push_back(input[i]);
		}
		else {
			if (!error_occured) {
				fprintf(stderr, "format error! unknown character has been ignored.\nresult after ignored:");
			}
			error_occured = true;
			input.erase(input.begin() + i);
			i--;
		}
	}
	switch (op) {
		case '+': return big_number_add(big_number(a_str), big_number(b_str));break;
		case '-': return big_number_minus(big_number(a_str), big_number(b_str));break;
		case '*': return big_number_multiply(big_number(a_str), big_number(b_str));break;
		case '/': return big_number_divide(big_number(a_str), big_number(b_str),7);break;
		default:break;
	}
}

void big_number::clear_zero() {
	for (int i = decimal.length() - 1;i >= 0;i--) {//埃计翴程箂
		if (decimal[i] == '0') {
			decimal.pop_back();
		}
		else {
			break;
		}
	}
	for (int i = 0;i != (integer.length() - 1);) {//埃俱计程玡箂
		if (integer[i] == '0') {
			integer.erase(integer.begin());
		}
		else {
			break;
		}
	}
}

big_number big_number_divide(big_number a, big_number b, int max_decimal_digit) {
	big_number result;
	big_number divide_1("1");
	if (b.integer.length() < 2 && b.decimal.length() == 0 && b.integer[0] == '0') {//筁納b0猵
		result.error_message = "can't divide by 0 it's not exist!";
		return result;
	}
	if (a.sign != b.sign) {//タ璽 or 璽タ 眔璽
		a.sign = true;	b.sign = true;
		result.sign = false;
	}
	//std::string all_number_a = a.integer + a.decimal;
	std::string all_number_b = b.integer + b.decimal;
	if (big_number_compare(b, divide_1) > 0) {
		
	}
	return result;
}

big_number big_number_remainder(big_number, big_number) {//緇计
	big_number result;
	return result;
}

void big_number::clear(void) {//睲埃
	integer.clear();
	integer = "";
	decimal.clear();
	decimal = "";	
	error_message.clear();
	error_message = "";
	numerator.clear();
	numerator = "";
	denominator.clear();
	denominator = "";
	sign = true;
	pre_operator = '+';
}

big_number big_number_factorial(big_number a) {//顶
	big_number result;
	return result;
}
big_number big_number_power(big_number a,big_number b) {//Ωよ
	big_number result;
	return result;
}
big_number big_number_root(big_number a, big_number b) {//秨碭(b)よ
	big_number result;
	return result;
}

void big_number::print(int) {

}