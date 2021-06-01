#include <iostream>
#include <vector>

using namespace std;

int main(){
	int V, L;
	vector<int> legs;
	int pos;
	while (cin >> V >> L) {
		legs.resize(L);
		for (int i = 0; i < L; i++) {
			cin >> legs[i];
		}
		cin >> pos;

		for (int i = 0; i < L; i++) {
			if (legs[i] == pos) {
				pos = pos + 1;
			}
			else if (legs[i] == pos - 1) {
				pos = pos - 1;
			}
		}
		cout << pos << endl;
	}
	return 0;
}