#include <iostream>
#include <set>
#include <string>
#include <fstream>
using namespace std;

int main() {
    set<string> name;
    fstream file;
    string input;
    file.open("name.txt",ios::in);
    while (getline(file, input)) {
        name.insert(input);
    }
    for (set<string>::iterator i = name.begin();i != name.end();i++) {
        cout << *i << endl;
    }
    return 0;
}