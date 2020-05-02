#include <iostream>
#include <string>
#include "Password.h"
#include "User.h"
using namespace std;
using namespace Authenticate;
int main() {
	inputUserName();
	cout << getUserName();
	inputPassword();
	cout << getPassword();
	return 0;
}