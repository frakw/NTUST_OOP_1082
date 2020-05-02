#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdio>
using namespace std;
inline char nc();
int main() {
    string input;
    vector<int> number;
    while (getline(cin, input)) {
        int len = 0, temp;
        len = 0;
        while (cin >> temp){
            if (temp > len) {
                len = temp;
            }
            number.push_back(temp);
            if (getchar() == '\n') { break; }
        }
        len++;
        for (int i = 0;i < input.length();i++) {
            if (input[i] == ' ') {
                input[i] = '_';
            }
        }
        int col = ceil((double)input.length() / (double)len);
        for (int i = 0;i < number.size();i++) {
            for (int j = 0;j < col;j++) {
                if ((j * len + number[i]) < input.length()) {
                    cout << input[j * len + number[i]];
                }
            }
        }
        cout << endl;
        number.clear();
    }
    return 0;
}
inline char nc() {
    static char buf[100000], * p1 = buf, * p2 = buf;
    return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, 100000, stdin), p1 == p2) ? EOF : *p1++;
}
/*
Row Transposition
3 0 6 1 2 5 4

int main(void){return 0;}
3 0 4 1 2

Apple
0 1 2 3 4 5 6 7 8 9 10


*/
