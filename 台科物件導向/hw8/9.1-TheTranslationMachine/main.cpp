#include <iostream>
#include <string>
#include <vector>
typedef struct {
	char a, b;
}letter_pair;
using namespace std;
void create_replace_letter(letter_pair*, vector<char>*,char, char,int);//遞迴尋找可替代字元
int main() {
	int m, n;
	while (cin >> m >> n) {
		if (!(m || n)) {
			break;
		}
		vector<char> replace[26];//a~z的可替代字元
		letter_pair* pair = new letter_pair[m];//動態配置給所有的字元對
		for (int i = 0;i < m;i++) {
			cin >> pair[i].a >> pair[i].b;//OJ不可用cin.get();
		}
		for (char i = 'a';i <= 'z';i++) {//從a~z填入
			replace[i - 'a'].push_back(i);//放入自己，之後才不用多檢查自己(迴圈一次到位)
			create_replace_letter(pair, replace,i,i,m);//遞迴尋找可替代字元
		}
		delete[] pair;//釋放
		for (int i = 0;i < n;i++) {
			string a, b;
			cin >> a >> b;
			if (a.length() != b.length()) {//不等長，直接no，然後下一筆
				cout << "no" << endl;
				continue;
			}
			int same_count = 0;//成功翻譯的數量
			for (int j = 0;j < b.length();j++) {
				for (int k = 0;k < replace[a[j] - 'a'].size();k++) {//從a的第幾個元素抓出整個字母的vector，然後跑過整個vector
					if (b[j] == replace[a[j] - 'a'][k] ){//如果成功翻譯
						same_count++;
						break;
					}
				}
			}
			cout << ((same_count == b.length())?"yes":"no") << endl;
		}
	}
    return 0;
}

void create_replace_letter(letter_pair* pair,vector<char>* replace,char main_letter,char letter,int m) {//main letter 是此遞迴主要儲存的字元，letter負責探索
	for (int i = 0;i < m;i++){
		if (pair[i].a == letter) {
			int j;
			for (j = 0;j < replace[main_letter - 'a'].size();j++) {//篩選掉已重複字元
				if (replace[main_letter - 'a'][j] == pair[i].b) {
					break;
				}
			}
			if (j == replace[main_letter - 'a'].size()) {
				replace[main_letter - 'a'].push_back(pair[i].b);//加入新可替代字元
				create_replace_letter(pair, replace, main_letter, pair[i].b, m);//新可替代字元遞迴
			}
		}
	}
}