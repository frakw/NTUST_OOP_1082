#include <iostream>
#include <vector>
#include <algorithm>
#include<cstdio>
using std::endl;

typedef struct _num_count {
	int flag;//數字
	int count;//出現次數
}num_count;

bool compare_with_flag(num_count&, num_count&);

int main() {
	std::vector<num_count> arr;
	std::vector<num_count>::iterator i = arr.begin();
	int num;
	while (std::cin >> num) {
		for (i = arr.begin();i != arr.end();i++) {
			if (num == i->flag) {
				(i->count)++;
				break;
			}
		}
		if (i == arr.end()) {
			arr.push_back({ num,1 });
		}
	}
	std::sort(arr.begin(), arr.end(), compare_with_flag);
	std::cout << "N\tcount\n";
	for (i = arr.begin();i != arr.end();i++) {
		printf("%d\t%d\n", i->flag, i->count);
	}


	return 0;
}

bool
compare_with_flag(num_count& a, num_count& b) {
	return a.flag > b.flag;
}
