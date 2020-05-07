#pragma once
using namespace std;
#include <iostream>
#include <string>
#include "Document.h"
class File : public Document {
public:
	File():pathname("") {}
	File(string text_in, string pathname_in) :Document(text_in), pathname(pathname_in) {}
	string getPathname() {
		return pathname;
	}
	void setPathname(string in) {
		pathname = in;
	}
private:
	string pathname = "";
};