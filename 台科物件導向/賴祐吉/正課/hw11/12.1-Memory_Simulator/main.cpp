#include <iostream>
#include <string>
using namespace std;
bool my_memcpy(void*,const void*,size_t);
int main() {
    int total_byte;
    int case_num;
    char* mem = nullptr;
    while (cin >> total_byte >> case_num) {
        mem = new char [total_byte] {};
        string command, type;
        int position;
        string str_in;
        unsigned int int_in;
        unsigned short short_in;
        unsigned char char_in;
        for (int i = 0;i < case_num;i++){
            cin >> command >> position >> type;
            if (position < 0) {
                cout << "Violation Access." << endl;
                continue;
            }
            if (type == "String") {
                if (command == "Set") {
                    cin >> str_in;
                    if (position + str_in.size() >= total_byte) {// \0 bug
                        cout << "Violation Access." << endl;
                        if (command == "Set") my_memcpy((void*)(mem + position), (const void*)str_in.c_str(),(size_t)total_byte - (size_t)position);
                        continue;
                    }
                    if (!my_memcpy((void*)(mem + position), (const void*)str_in.c_str(), str_in.size())) {
                        cout << "copy memory error" << endl;
                    }
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
                        my_memcpy((void*)(mem + position), (const void*)(&int_in), (size_t)total_byte - (size_t)position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> int_in;
                    if(!my_memcpy((void*)(mem + position), (const void*)(&int_in), sizeof(int))) {
                        cout << "copy memory error" << endl;
                    }
                }
                else if (command == "Get") {
                    if (!my_memcpy((void*)(&int_in), (const void*)(mem + position), sizeof(int))) {
                        cout << "copy memory error" << endl;
                    }
                    cout << int_in << endl;
                }
            }
            else if (type == "short") {
                if (position + 2 > total_byte) {
                    cout << "Violation Access." << endl;
                    if (command == "Set") {
                        cin >> short_in;
                        my_memcpy((void*)(mem + position), (const void*)(&short_in), (size_t)total_byte - (size_t)position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> short_in;
                    if (!my_memcpy((void*)(mem + position), (const void*)(&short_in), sizeof(short))) {
                        cout << "copy memory error" << endl;
                    }
                }
                else if (command == "Get") {
                    if (!my_memcpy((void*)(&short_in), (const void*)(mem + position), sizeof(short))) {
                        cout << "copy memory error" << endl;
                    }
                    cout << short_in << endl;
                }
            }
            else if (type == "char") {
                int tmp;
                if (position + 1 > total_byte) {
                    cout << "Violation Access." << endl;
                    if (command == "Set") {
                        cin >> tmp;
                        my_memcpy((void*)(mem + position), (const void*)(&char_in), (size_t)total_byte - (size_t)position);
                    }
                    continue;
                }
                if (command == "Set") {
                    cin >> tmp;
                    if (!my_memcpy((void*)(mem + position), (const void*)(&tmp), sizeof(char))) {
                        cout << "copy memory error" << endl;
                    }
                }
                else if (command == "Get") {
                    if (!my_memcpy((void*)(&char_in), (const void*)(mem + position), sizeof(char))) {
                        cout << "copy memory error" << endl;
                    }
                    cout << (int)char_in << endl;
                }
            }
        }
        delete[] mem;
        mem = nullptr;
    }
    return 0;
}

bool my_memcpy(void* dest, const void* src, size_t n)
{
    const char* csrc = (const char*)(src);//reinterpret_cast<const char*>
    char* cdest = (char*)(dest);//reinterpret_cast<char*>
    for (int i = 0; i < n; i++) {
        cdest[i] = csrc[i];
    }
    for (int i = 0; i < n; i++) {//check copy
        if (cdest[i] != csrc[i]) {
            return false;
        }
    }
    return true;
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