#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <cstdio>
using namespace std;
//肈ヘ弧:块︽﹃钡ㄓΤ碭计程计盢﹃パτパオτ逼row羆计程计钡ㄓ–计赣row计﹃フ┏絬块
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
        int col = ceil((double)input.length() / (double)len);//ノrow羆计(len)璸衡col羆计よ獽ぇfor癹伴ㄏノ
        for (int i = 0;i < number.size();i++) {//–计┮﹃块
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

/*
Row Transposition
3 0 6 1 2 5 4

int main(void){return 0;}
3 0 4 1 2

Apple
0 1 2 3 4 5 6 7 8 9 10


*/
