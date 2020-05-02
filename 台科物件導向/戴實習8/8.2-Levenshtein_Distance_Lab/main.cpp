#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;
int main() {
	string a, b;
	while (getline(cin,a)) {
		getline(cin, b);
		if (a.length() == 0) {
			cout << b.length();
			continue;
		}
		else if (b.length() == 0) {
			cout << a.length();
			continue;
		}
		int** matrix = new int* [b.length() + 1]{};
		for (int i = 0;i <= b.length();i++) {
			matrix[i] = new int[a.length() + 1]{};
			if (i == 0) {
				for (int j = 0;j <= a.length();j++) {
					matrix[i][j] = j;
				}
			}
			else {
				matrix[i][0] = i;
			}
		}
		for (int i = 1;i <= b.length();i++) {
			for (int j = 1;j <= a.length();j++) {
				int temp = !(a[j-1] == b[i-1]);
				matrix[i][j] = min({ matrix[i - 1][j] + 1 ,matrix[i][j - 1] + 1 ,matrix[i - 1][j - 1] + temp });
			}
		}
		cout << matrix[b.length()][a.length()] << endl;
		for (int i = 0;i <= b.length();i++) {
			delete[] matrix[i];
		}
		delete[] matrix;
	}
    return 0;
}
