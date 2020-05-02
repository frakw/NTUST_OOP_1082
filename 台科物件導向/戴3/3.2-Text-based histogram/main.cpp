#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
using std::endl;

typedef struct _num_count {
	int flag;//數字
	int count;//出現次數
}num_count;

int main() {
	num_count grade[6];
	for (int i = 0;i < 6;i++) { grade[i] = { i,0 }; }
	int input;
	while (std::cin >> input) {
		grade[input].count++;
	}
	for (int i = 0;i < 6;i++) {
		std::cout << grade[i].count << " grade(s) of " << i << endl;
	}
	return 0;
}