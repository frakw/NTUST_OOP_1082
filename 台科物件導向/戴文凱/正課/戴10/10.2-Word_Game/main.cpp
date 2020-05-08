#include <iostream>
#include <fstream>
#include <string>
using namespace std;
typedef struct _coord {
	int x, y;
	_coord(int a, int b) :x(a), y(b) {}
}coord;
typedef struct {
	char alpha;
	bool has_been = false;
}Grid;
class Table {
public:
	Grid grid[4][4];
	void input() {
		for (int i = 0;i < 4;i++) {
			for (int j = 0;j < 4;j++) {
				cin >> this->grid[i][j].alpha;
			}
			cin.ignore();
		}
	}
	Grid& position(coord pos) {
		return grid[pos.y][pos.x];
	}
};

bool check_word(Table table, string word);
bool check_word(Table table, string word, coord);

int main() {
	Table table;
	table.input();
	fstream input;
	input.open("words.txt", ios::in);
	string word;
	while (input >> word) {
		if (check_word(table, word)) {
			cout << word << endl;
		}
	}
	return 0;
}

bool check_word(Table table, string word) {
	for (int i = 0;i < 4;i++) {
		for (int j = 0;j < 4;j++) {
			if (word[0] == table.grid[i][j].alpha) {
				coord tmp{ j,i };
				if (check_word(table, word, tmp)) {
					return true;
				}
			}
		}
	}
	return false;
}

bool check_word(Table table, string word, coord pos) {
	if (pos.x < 0 || pos.y < 0 || pos.x>3 || pos.y>3 || table.position(pos).has_been) return false;
	if (!word.length())return true;
	if (word[0] == table.position(pos).alpha) {
		coord direction[8] = { {pos.x + 1,pos.y},{pos.x - 1,pos.y},{pos.x,pos.y + 1},{pos.x,pos.y - 1},{pos.x - 1,pos.y - 1},{pos.x + 1,pos.y - 1},{pos.x - 1,pos.y + 1}, {pos.x + 1,pos.y + 1} };
		table.position(pos).has_been = true;
		for (int i = 0; i < 8;i++) {
			if (check_word(table, word.substr(1), direction[i])) {
				return true;
			}
		}
	}
	return false;
}