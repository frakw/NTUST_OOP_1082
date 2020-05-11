#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include<windows.h>
using namespace std;
#define road_color 55
#define dot_color 160
#define road_width 2
void gotoxy(int xpos, int ypos);
void SetColor(int color = 7);
//test xy : 117 60, 75 35
class Maze {
public:
	Maze() {
		row = 10;
		col = 10;
	}
	Maze(int, int);
	~Maze();
	
	void create(bool, time_t delay);
	bool** maze_01() {
		return map;
	}
	void print(string,string);
	void print();
private:
	string road = "  ";
	string wall = "¢i";//¢i
	void new_memory(int,int);
	int row = 10;
	int col = 10;
	bool** visited = nullptr;
	bool** map = nullptr;
	stack<pair<int, int>> coord_record;//x,y
};
int main() {
	//system("mode con cols=300 lines=50");
	srand(time(NULL));
	int row, col;
	cout << "Maze x * y :";
	cin >> col >> row;
	Maze maze(col,row);
	maze.create(true,5);
	if (!(col % 2)) col++;
	if (!(row % 2)) row++;
	fstream output;
	output.open("maze.txt", ios::out);
	bool** maze_storage = maze.maze_01();
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (maze_storage[i][j]) {
				output << '1';
			}
			else {
				output << '0';
			}
		}
		output << '\n';
	}
	output.close();
	SetColor();
	gotoxy(0, row + 1);
	system("pause");
	return 0;
}
Maze::Maze(int col_i, int row_i):col(col_i),row(row_i){
}
void Maze::new_memory(int col_i, int row_i) {
	if (visited != nullptr || map != nullptr) {
		this->~Maze();
	}
	if (col_i < 2 || row_i < 2) {
		cout << "maze too small\n";
		return;
	}
	if (!(col_i % 2)) col_i++;
	if (!(row_i % 2)) row_i++;
	this->row = row_i;
	this->col = col_i;
	visited = new bool* [row] {};
	map = new bool* [row] {};
	for (int i = 0;i < row;i++) {
		visited[i] = new bool[col] {};
		map[i] = new bool[col] {};
		if (!(i % 2)) {
			for (int j = 0;j < col;j++) {
				map[i][j] = 1;
				//visited[i][j] = true;
			}
		}
		else {
			for (int j = 0;j < col;j += 2) {
				map[i][j] = 1;
				//visited[i][j] = true;
			}
		}
	}
}

Maze::~Maze() {
	for (int i = 0;i < row;i++) {
		delete[] visited[i];
		delete[] map[i];
	}
	delete[] visited;
	delete[] map;
	visited = nullptr;
	map = nullptr;
}
void Maze::create(bool animate_on = false, time_t delay = 50) {
	if (visited != nullptr || map != nullptr) {
		this->~Maze();
	}
	new_memory(col, row);
	if (animate_on) {
		gotoxy(0, 0);
		for (int i = 0;i < row;i++) {
			for (int j = 0;j < col;j++) {
				cout << wall;
			}
			cout << '\n';
		}
	}
	int visited_count = 1;
	int max_count = (int)(row/2)*(int)(col/2);
	int x=1, y=1 ,prex=1,prey=1;
	visited[1][1] = true;
	coord_record.push(make_pair(1, 1));
	while (1) {

		vector<int> neighbours;
		if (y - 2 > 0) {
			if (!visited[y - 2][x]) {//up
				neighbours.push_back(0);
			}
		}
		if(y + 3 < row){
			if (!visited[y + 2][x]) {//down
				neighbours.push_back(1);
			}
		}
		if (x - 2 > 0) {
			if (!visited[y][x - 2]) {//left
				neighbours.push_back(2);
			}
		}
		if (x + 3 < col) {
			if (!visited[y][x + 2]) {//right
				neighbours.push_back(3);
			}
		}
		map[y][x] = 0;
		if (animate_on) {
			gotoxy(road_width * prex, prey);
			SetColor(road_color);
			cout << road;
			gotoxy(road_width * x, y);
			SetColor(dot_color);
			cout << road;
			gotoxy(0, 0);
			Sleep(delay);
			if (visited_count == max_count) {
				break;
			}
		}
		prex = x;
		prey = y;
		if (neighbours.empty()) {
			x = coord_record.top().first;
			y = coord_record.top().second;
			coord_record.pop();
			continue;
		}
		switch (neighbours[rand() % neighbours.size()]) {
		case 0:
			coord_record.push(make_pair(x, y - 2));
			visited[y - 2][x] = true;
			map[y - 1][x] = 0;

			if (animate_on) {
				SetColor(road_color);
				gotoxy(road_width * x, y-1);
				cout << road;
				gotoxy(0, 0);
				Sleep(delay);
			}
			y -= 2;
			break;
		case 1:
			coord_record.push(make_pair(x, y + 2));
			visited[y + 2][x] = true;
			map[y + 1][x] = 0;

			if (animate_on) {
				SetColor(road_color);
				gotoxy(road_width * x, y+1);
				cout << road;
				gotoxy(0, 0);
				Sleep(delay);
			}
			y += 2;
			break;
		case 2:
			coord_record.push(make_pair(x - 2, y));
			visited[y][x - 2] = true;
			map[y][x - 1] = 0;

			if (animate_on) {
				SetColor(road_color);
				gotoxy(road_width * (x-1), y);
				cout << road;
				gotoxy(0, 0);
				Sleep(delay);
			}
			x -= 2;
			break;
		case 3:
			coord_record.push(make_pair(x + 2, y));
			visited[y][x + 2] = true;
			map[y][x + 1] = 0;

			if (animate_on) {
				SetColor(road_color);
				gotoxy(road_width * (x + 1), y);
				cout << road;
				gotoxy(0, 0);
				Sleep(delay);
			}
			x += 2;
			break;
		}
		visited_count++;
	}
}
void Maze::print(string wall_i, string road_i) {
	wall = wall_i;
	road = road_i;
	this->print();
}

void Maze::print() {
	if (visited == nullptr || map == nullptr) {
		new_memory(this->col, this->row);
		this->create();
	}
	for (int i = 0;i < row;i++) {
		for (int j = 0;j < col;j++) {
			if (map[i][j]) {
				cout << wall;
			}
			else {				
				cout << road;
			}
		}
		cout << '\n';
	}
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void SetColor(int color )
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}