#include <iostream>
#include <string>
#include <ctype.h>
using namespace std;
void charsegmentdisplay(char[],int);//char版 開頭可以是0

const bool segment[10][9][3] = {
{{1,1,1},{1,0,1},{1,1,1}},//0
{{1,0,1},{0,0,1},{0,0,1}},//1
{{1,1,1},{0,1,1},{1,1,0}},//2
{{1,1,1},{0,1,1},{0,1,1}},//3
{{1,0,1},{1,1,1},{0,0,1}},//4
{{1,1,1},{1,1,0},{0,1,1}},//5
{{1,1,1},{1,1,0},{1,1,1}},//6
{{1,1,1},{0,0,1},{0,0,1}},//7
{{1,1,1},{1,1,1},{1,1,1}},//8
{{1,1,1},{1,1,1},{0,1,1}} //9
};
const char display[3][3] = {
  {' ','_',' '},
  {'|','_','|'},
  {'|','_','|'} };
int main() {
	string input;
	while (getline(cin,input)) {
		for (int i = 0;i < input.length();i++) {
			if (!isdigit(input[i])) {
				input.erase(input.begin() + i);
				i--;
			}
		}
		for (int i = 0;i < 3;i++) {
			for (int g = 0;g < input.length();g++) {
				for (int j = 0;j < 3;j++) {
					printf("%c", segment[input[g]-'0'][i][j] ? display[i][j] : ' ');
				}
				//if(g!=input.length()-1)printf(" ");
				//printf("%s", (input[g + 1]-'0') != 1 && g < (input.length()-1) ? " " : "");
			}
			printf("\n");
		}
	}
    return 0;
}


void charsegmentdisplay(char a[], int q) {
	int i, j, g, m;
	int k[100], h = -1;
	for (m = 0;m <= q;m++) {
		k[m] = a[m] - '0';
	}
	for (i = 0;i < 3;i++) {
		for (g = 0;g <= q;g++) {
			for (j = 0;j < 3;j++) {
				printf("%c", segment[k[g]][i][j] ? display[i][j] : ' ');
			}
			printf("%s", k[g + 1] != 1 && g < q ? " " : "");
		}
		printf("\n");
	}
}