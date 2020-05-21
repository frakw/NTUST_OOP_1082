#include <iostream>
#include <string>
#include <memory.h>
using namespace std;
int main() {
    unsigned int total_byte;
    int case_num;
    char* mem = nullptr;
    while (cin >> total_byte >> case_num) {
        mem = new char [total_byte] {};
        string command, type;
        unsigned int position;
        string str_in;
        unsigned int int_in;
        unsigned short short_in;
        unsigned char char_in;
        for (int i = 0;i < case_num;i++) {
            cin >> command >> position >> type;
            if (position < 0 || position >= total_byte) {
                cout << "Violation Access." << endl;
                continue;
            }
            if (type == "String") {
                if (command == "Set") {
                    cin >> str_in;
                    if (position + str_in.size() >= total_byte) {// \0 bug
                        cout << "Violation Access." << endl;
                        if (command == "Set") memcpy(mem + position,str_in.c_str(),total_byte - position);
                        continue;
                    }
                    memcpy(mem + position,str_in.c_str(), str_in.size());
                }
                else if (command == "Get") {
                    char* p = mem + position;
                    int i = position;
                    while (*p != '\0' && i < total_byte) {
                        cout << (char)(*p);
                        p++;
                        i++;
                    }
                    cout << endl;
                }
            }
            else if (type == "int") {
                if (position + 4 > total_byte) {
                    cout << "Violation Access." << endl;
                    if (command == "Set") {
                        cin >> int_in;
                        memcpy(mem + position,&int_in,total_byte - position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> int_in;
                    memcpy(mem + position, &int_in, sizeof(int));
                }
                else if (command == "Get") {
                    memcpy(&int_in,mem + position, sizeof(int));
                    cout << int_in << endl;
                }
            }
            else if (type == "short") {
                if (position + 2 > total_byte) {
                    cout << "Violation Access." << endl;
                    if (command == "Set") { 
                        cin >> short_in;
                        memcpy(mem + position,&short_in, total_byte - position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> short_in;
                    memcpy(mem + position, &short_in, sizeof(short));
                }
                else if (command == "Get") {
                    memcpy(&short_in, mem + position, sizeof(short));
                    cout << short_in << endl;
                }
            }
            else if (type == "char") {
                int tmp;
                if (position + 1 > total_byte) {
                    cout << "Violation Access." << endl;
                    if (command == "Set") {
                        cin >> tmp;
                        memcpy(mem + position,&char_in,total_byte - position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> tmp;
                    memcpy(mem + position, &tmp, sizeof(char));
                }
                else if (command == "Get") {
                    memcpy(&char_in,mem + position, sizeof(char));
                    cout << (int)char_in << endl;
                }
            }
        }
        delete[] mem;
        mem = nullptr;
    }
    return 0;
}
/*
1000
6
Set 0 String Hi
Set 1 int 3158064
Set 4 short 13878
Set 6 char 0
Get 0 String
Get 1000 int


6

5

Set 0 String Hi

Set 2 char 33

Get 0 String

Set 1 int 1869376613

Get 0 String

*/