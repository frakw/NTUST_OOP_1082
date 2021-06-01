#include <iostream>
#include <queue>
#include <vector>

using namespace std;

int main(){
	int w, h;
	while (cin >> w >> h) {

		vector<vector<int>> img(w, vector<int>(h));
		for (int i = 0; i < h; i++) {
			for (int j = 0; j < w; j++) {
				cin >> img[j][i];
			}
		}

		int x, y;

		cin >> x >> y;

		queue<pair<int, int>> visit;
		visit.push(make_pair(x, y));

		int count = 0;

		while (!visit.empty())
		{
			pair<int, int> pos = visit.front();
			visit.pop();

			if (pos.first >= 0 && pos.second >= 0 && pos.first < w && pos.second < h && img[pos.first][pos.second] == 0) {
				img[pos.first][pos.second] = 1;
				count += 1;
				visit.push(make_pair(pos.first + 1, pos.second));
				visit.push(make_pair(pos.first - 1, pos.second));
				visit.push(make_pair(pos.first, pos.second + 1));
				visit.push(make_pair(pos.first, pos.second - 1));
			}
		}

		cout << count << endl;
	}

	return 0;
}