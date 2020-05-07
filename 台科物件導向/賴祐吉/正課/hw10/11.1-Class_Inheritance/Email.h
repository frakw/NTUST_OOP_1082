#pragma once
#include <iostream>
#include <string>
#include "Document.h"
using namespace std;
class Email : public Document{
public:
	Email() : Document(""), sender(""), recipient(""), title("") {		
	}
	Email(string text,string a, string b, string c): Document(text),sender(a),recipient(b),title(c){
	}
	const string getSender() const{
		return sender;
	}
	const string getRecipient() const {
		return recipient;
	}
	const string getTitle() const {
		return title;
	}
private:
	string sender="";
	string recipient="";
	string title="";
};