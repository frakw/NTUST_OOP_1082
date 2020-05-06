#include <iostream>
#include <cstdio>
#include <string>
using namespace std;
class employer {
public:
    string name;
    string salary;
    string bonus;
};
int main() {
    int case_num;
    int i;
    while (cin >> case_num) {
        employer* man=new employer[case_num];
        size_t max_len[3] = {0,0,0};
        for (int i = 0;i < case_num;i++) {
            cin >> man[i].name;
            cin >> man[i].salary;
            cin >> man[i].bonus;
        }
        for (int j = 0;j < case_num;j++) {
            if (man[j].name.length() > max_len[0]) {
                max_len[0] = man[j].name.length();
            }
            if (man[j].salary.length() > max_len[1]) {
                max_len[1] = man[j].salary.length();
            }
            if (man[j].bonus.length() > max_len[2]) {
                max_len[2] = man[j].bonus.length();
            }
        }
        for (int j = 0;j < case_num;j++) {
            for (int k = 0;k < (max_len[0] - man[j].name.length());k++) {
                cout << " ";
            }
            cout << man[j].name <<"|  ";
            for (int k = 0;k < (max_len[1] - man[j].salary.length() );k++) {
                cout << " ";
            }
            cout << man[j].salary << "|  ";
            for (int k = 0;k < (max_len[2] - man[j].bonus.length() );k++) {
                cout << " ";
            }
            cout << man[j].bonus << endl;
        }
    }
    return 0;
}