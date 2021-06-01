#include <iostream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

using namespace std;

// a class to manage the island
// x === j === column, y === i === row
// pt.first === x, pt.second === y
class Island
{
private:
	vector<pair<int, int>> points;
public:
	Island();
	Island(int i, int j);
	~Island() {}
	vector<pair<int, int>> retPoints();
	void pushPoint(int i, int j);
	void combine(Island land);
	bool exist(int x, int y)const;
	int sealine()const;
	int area()const;
};

// some function to read data from map
bool outOfRange(int i, int j);
bool isSea(int i, int j);
int existInOther(int i, int j);
bool attachToOther(int i, int j);

// global variable to store map
int h, w; // height, width
vector<string> m; // map
vector<Island> islands;

int main() {
	cin >> h >> w;
	cin.get();
	m.resize(h);
	for (int i = 0; i < h; i++)
		getline(cin, m[i]);
	for (int i = 0; i < h; i++)
		for (int j = 0; j < w; j++)
			if (m[i][j] == '#' && !attachToOther(i, j)) {
				Island l(i, j);
				islands.push_back(l);
			}
	sort(islands.begin(), islands.end(), [](const Island &lhs, const Island &rhs) -> bool
	{
		if (lhs.area() == rhs.area()) return lhs.sealine() > rhs.sealine();
		return lhs.area() > rhs.area();
	});
	for (Island l : islands) {
		cout << l.area() << " " << l.sealine() << endl;
	}
	return 0;
}

Island::Island(int i, int j) {
	points.push_back(make_pair(j, i));
}

vector<pair<int, int>> Island::retPoints() {
	return points;
}

void Island::pushPoint(int i, int j) {
	points.push_back(make_pair(j, i));
}

void Island::combine(Island land) {
	vector<pair<int, int>> pts = land.retPoints();
	points.insert(points.end(), pts.begin(), pts.end());
}

bool Island::exist(int x, int y)const {
	return any_of(points.begin(), points.end(), [x, y](pair<int, int> pt) {
		return (pt.first == x && pt.second == y);
	});
}

int Island::sealine()const {
	int l = 0;
	for (const pair<int, int> pt : points) {
		if (isSea(pt.second - 1, pt.first) &&
			!exist(pt.first, pt.second - 1)) l++; // up
		if (isSea(pt.second + 1, pt.first) &&
			!exist(pt.first, pt.second + 1)) l++; // down
		if (isSea(pt.second, pt.first - 1) &&
			!exist(pt.first - 1, pt.second)) l++; // left
		if (isSea(pt.second, pt.first + 1) &&
			!exist(pt.first + 1, pt.second)) l++; // right
	}
	return l;
}

int Island::area()const {
	return points.size();
}

bool outOfRange(int i, int j) {
	if (i < 0 || i >= h) return true;
	if (j < 0 || j >= w) return true;
	return false;
}

bool isSea(int i, int j) {
	if (outOfRange(i, j)) return true;
	return m[i][j] == '.';
}

int existInOther(int i, int j) {
	if (isSea(i, j)) return -1;
	for (int l = 0; l < islands.size(); l++) {
		if (islands[l].exist(j, i)) return l;
	}
	return -1;
}

bool attachToOther(int i, int j) {
	// sibling finding
	int l = existInOther(i, j - 1),
		r = existInOther(i, j + 1),
		u = existInOther(i - 1, j),
		d = existInOther(i + 1, j);
	// left up combine
	if (l != -1 && u != -1 && l != u) {
		islands[u].combine(islands[l]);
		islands[u].pushPoint(i, j);
		islands.erase(islands.begin() + l);
		return true;
	}
	// land attaching
	if (l != -1) {
		islands[l].pushPoint(i, j);
		return true;
	}
	if (r != -1) {
		islands[r].pushPoint(i, j);
		return true;
	}
	if (u != -1) {
		islands[u].pushPoint(i, j);
		return true;
	}
	if (d != -1) {
		islands[d].pushPoint(i, j);
		return true;
	}
	return false;
}