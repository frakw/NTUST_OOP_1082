#pragma once
#include <iostream>
#include <string>
using namespace std;
class Document {
public:
	Document() {
		text = "";
	}
	Document(string in):text(in) {
	}
	Document& operator=(const Document& a){
		text = a.text;
		return *this;
	}
	const string getText() const{
		return text;
	}
private:
	string text="";
};