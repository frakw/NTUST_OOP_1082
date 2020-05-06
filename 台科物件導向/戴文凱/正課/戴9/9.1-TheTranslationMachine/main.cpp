#include <iostream>
#include <string>
#include <vector>


#define version1
//#define version2


typedef struct {
	char a, b;
#ifdef version2
	bool has_go = false;
#endif // version2
}letter_pair;
using namespace std;
#ifdef version1
void create_replace_letter(letter_pair*, vector<char>*, char, char, int);//遞迴尋找可替代字元
#endif // version1
#ifdef version2
bool check_char_link(letter_pair check_data, letter_pair* pair, int m);
#endif // version2
int main() {
	int m, n;
	while (cin >> m >> n) {
		if (!(m || n)) {
			break;
		}
		letter_pair* pair = new letter_pair[m];//動態配置給所有的字元對
		for (int i = 0;i < m;i++) {
			cin >> pair[i].a >> pair[i].b;//OJ不可用cin.get();
		}
#ifdef version1
		vector<char> replace[26];//a~z的可替代字元
		for (char i = 'a';i <= 'z';i++) {//從a~z填入
			replace[i - 'a'].push_back(i);//放入自己，之後才不用多檢查自己(迴圈一次到位)
			create_replace_letter(pair, replace, i, i, m);//遞迴尋找可替代字元
		}
#endif // version1
		for (int i = 0;i < n;i++) {
			string a, b;
			cin >> a >> b;
			if (a.length() != b.length()) {//不等長，直接no，然後下一筆
				cout << "no" << endl;
				continue;
			}
			int same_letter_count = 0;//成功翻譯的數量
#ifdef version1
			for (int j = 0;j < b.length();j++) {
				for (auto k : replace[a[j] - 'a']) {//從a的第幾個元素抓出整個字母的vector，然後跑過整個vector
					if (b[j] == k) {//如果成功翻譯
						same_letter_count++;
						break;
					}
				}
			}
			cout << ((same_letter_count == b.length()) ? "yes" : "no") << endl;
#endif // version1
#ifdef version2
			for (int j = 0;j < b.length();j++) {
				letter_pair new_pair;
				new_pair.a = a[j]; new_pair.b = b[j];
				for (int i = 0;i < m;i++) {
					pair[i].has_go = false;
				}
				if (!check_char_link(new_pair, pair, m)) {
					cout << "no" << endl;
					goto next_test;
				}
			}
			cout << "yes" << endl;	
		next_test:;		
#endif // version2		
		}
		delete[] pair;
	}
	return 0;
}
#ifdef version1
void create_replace_letter(letter_pair* pair, vector<char>* replace, char main_letter, char letter, int m) {//main letter 是此遞迴主要儲存的字元，letter負責探索
	for (int i = 0;i < m;i++) {
		if (pair[i].a == letter) {
			for (auto j : replace[main_letter - 'a']) {//篩選掉已重複字元
				if (j == pair[i].b) {
					goto do_next;
				}
			}
			replace[main_letter - 'a'].push_back(pair[i].b);//加入新可替代字元
			create_replace_letter(pair, replace, main_letter, pair[i].b, m);//新可替代字元遞迴
		}
	do_next:;
	}
}
#endif // version1
#ifdef version2
bool check_char_link(letter_pair check_data,letter_pair* pair,int m)//直接遞迴版本  check_data為2個要檢測的字元
{
	if (check_data.a == check_data.b) return true;
	for (int i = 0; i < m; i++)
	{
		if (!pair[i].has_go && pair[i].b == check_data.b )
		{
			pair[i].has_go = true;
			letter_pair tmp = check_data;
			tmp.b = pair[i].a;
			if (pair[i].a == check_data.a || check_char_link(tmp, pair, m)) {
				return true;
			}
		}
	}
	return false;
}
#endif // version2