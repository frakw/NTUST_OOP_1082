#pragma once
#include <iostream>
#include <string>
using namespace std;
class Log {
public:
	static void add_log(string input) {
		log += input;
	}
	static void add_err(string input) {
		error += input;
	}
	static string log;
	static string error;
};