#include <iostream>
#include <algorithm>

using namespace std;
typedef struct { int x; int y; }coord;
void print_map(char**, int, int);
#define out_of_range cout << "Out of range." << endl<<endl; goto loop_end;

void draw_line(char**,coord,coord);
int main() {
	int m, n;
	while (cin>>m>>n) {
		char** map = new char* [n] {};
		for (int i = 0;i < n;i++) {
			map[i] = new char[m];
			for (int j = 0;j < m;j++) {
				map[i][j] = '*';
			}
		}
		char command;
		while (cin >> command) {
			if (command == '\n') {
				continue;
			}
			if (command == 'E' || command == 'e') {
				break;
			}
			switch (command) {
			case'S':case's': {
				int width;
				coord origin;
				cin >> width >> origin.x >> origin.y;
				if (origin.y + width > n || origin.x + width > m || origin.x<0 || origin.y<0) {
					out_of_range;
				}
				for (int i = 0;i < width;i++) {
					for (int j = 0;j < width;j++) {
						map[origin.y+i][origin.x+j] = 'X';
					}
				}
			}break;
			case'T':case't': {
				int width;
				coord origin,lr_point,ud_point;
				char lr, ud;
				cin >> width >> origin.x >> origin.y >> lr >> ud;
				if (lr == 'L') {
					if (origin.x - width + 1 < 0) {
						out_of_range;
					}
					lr_point = { origin.x - width + 1, origin.y};
				}
				else {
					if (origin.x + width  > m) {
						out_of_range;
					}
					lr_point = { origin.x + width -1, origin.y };
				}
				if (ud == 'U') {
					if (origin.y - width +1 < 0) {
						out_of_range;
					}
					ud_point = { origin.x , origin.y - width +1};
				}
				else {
					if (origin.y + width > n) {
						out_of_range;
					}
					ud_point = { origin.x , origin.y + width-1 };
				}
				draw_line(map, origin, lr_point);
				draw_line(map, origin, ud_point);
				draw_line(map, lr_point, ud_point);
			}break;
			case'L':case'l': {
				coord start,end;
				cin >> start.x >> start.y >> end.x >> end.y;
				if (start.x < 0 || start.x >= m || start.y < 0 || start.y >= n || end.x < 0 || end.x >= m || end.y < 0 || end.y >= n) {
					out_of_range;
				}
				draw_line(map, start, end);
			}break;
			}
			print_map(map, m, n);
			cout << endl;
		loop_end:;
		}
		for (int i = 0;i < n;i++) {
			delete[] map[i];
		}
		delete[] map;
	}
    return 0;
}

void print_map(char** map,int m, int n) {
	for (int i = 0;i < n;i++) {
		for (int j = 0;j < m;j++) {
			cout << map[i][j];
		}
		cout << endl;
	}
}

void draw_line(char** map,coord a, coord b) {
	map[b.y][b.x] = 'X';
	for (int i = a.y, j = a.x ;i!=b.y || j!=b.x;i+=(i < b.y ? 1:(i==b.y?0:-1)), j+=(j < b.x ? 1 : (j == b.x ? 0 : -1))) {
		map[i][j] = 'X';
	}
}