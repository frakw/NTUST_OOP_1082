//#include <iostream>
//#include <Windows.h>
//
//
//int main()
//{
//	//get console handler
//	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
//	if (h == NULL)
//	{
//		return false; // console not found
//	}
//	//set console mode, enable window and mouse input
//	DWORD cNumRead, fdwMode, i;
//	fdwMode = ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT;
//	if (!SetConsoleMode(h, fdwMode))
//		fprintf(stderr, "%s\n", "SetConsoleMode");
//	//get input
//	DWORD cc;
//	INPUT_RECORD irec;
//	KEY_EVENT_RECORD key;
//	MOUSE_EVENT_RECORD mouse;
//	for (; ; )
//	{
//		ReadConsoleInput(h, &irec, 1, &cc);
//		//mouse input
//		if (irec.EventType == MOUSE_EVENT)
//		{
//			mouse = (MOUSE_EVENT_RECORD&)irec.Event;
//			switch (mouse.dwButtonState)
//			{
//			case FROM_LEFT_1ST_BUTTON_PRESSED:
//				std::cout << "mouse left click" << std::endl;
//				std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
//				break;
//			case RIGHTMOST_BUTTON_PRESSED:
//				std::cout << "mouse right click" << std::endl;
//				std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
//				break;
//			case FROM_LEFT_2ND_BUTTON_PRESSED:
//				std::cout << "mouse middle click" << std::endl;
//				std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
//				break;
//			default:
//				break;
//			}
//
//			switch (mouse.dwEventFlags)
//			{
//			case DOUBLE_CLICK:
//				std::cout << "mouse DOUBLE_CLICK" << std::endl;
//				break;
//			case MOUSE_WHEELED:
//				std::cout << "mouse MOUSE_WHEELED:" << HIWORD(mouse.dwButtonState) << std::endl;
//				break;
//			default:
//				break;
//			}
//		}
//		else if (irec.EventType == KEY_EVENT)
//		{
//			key = (KEY_EVENT_RECORD&)irec.Event;
//			if (key.bKeyDown)
//			{
//				if (key.wVirtualKeyCode == VK_F1)
//				{
//					std::cout << "F1" << std::endl;
//				}
//				else
//				{
//					std::cout << "key: " << key.uChar.AsciiChar
//						<< " code:  " << key.wVirtualKeyCode << std::endl;
//				}
//	
//			}
//
//
//		}
//	}
//}



#include<iostream>
#include<fstream>
#include <string>
#include <vector>
#include <stack>
#include <ctime>
#include<windows.h>
using namespace std;
#define the_road "  "
#define the_wall "¢i"
#define road_color 55
#define dot_color 160
#define road_x_width 2
#define source_dot_color 155
#define dest_dot_color 75
void gotoxy(int xpos, int ypos);
void SetColor(int color = 7);
pair<COORD,COORD> choose_dot();
//test xy : 117 60
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
	void print(string, string);
	void print();
	void output(string filename) {
		if (map == nullptr) {
			return;
		}
		fstream output;
		output.open(filename, ios::out);
		for (int i = 0;i < row;i++) {
			for (int j = 0;j < col;j++) {
				if (map[i][j]) {
					output << '1';
				}
				else {
					output << '0';
				}
			}
			output << '\n';
		}
		output.close();
	}
private:
	string road = the_road;
	string wall = the_wall;//¢i
	bool new_memory(int, int);
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
	Maze maze(col, row);
	maze.create(true, 5);
	maze.output("maze.txt");//update stack_maze
	choose_dot();
	system("pause");
	return 0;
}
Maze::Maze(int col_i, int row_i) :col(col_i), row(row_i) {
}
bool Maze::new_memory(int col_i, int row_i) {
	if (visited != nullptr || map != nullptr) {
		this->~Maze();
	}
	if (col_i < 2 || row_i < 2) {
		cout << "maze too small\n";
		return false;
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
			}
		}
	}
	return true;
}

Maze::~Maze() {
	if (map != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] map[i];
		}
		delete[] map;
		map = nullptr;
	}
	if (visited != nullptr) {
		for (int i = 0;i < row;i++) {
			delete[] visited[i];
		}
		delete[] visited;
		visited = nullptr;
	}
}
void Maze::create(bool animate_on = false, time_t delay = 50) {
	if (visited != nullptr || map != nullptr) {
		this->~Maze();
	}
	if (!new_memory(col, row)){
		return;
	}
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
	int max_count = (int)(row / 2) * (int)(col / 2);
	int x = 1, y = 1, prex = 1, prey = 1;
	visited[1][1] = true;
	coord_record.push(make_pair(1, 1));
	while (1) {

		vector<int> neighbours;
		if (y - 2 > 0) {
			if (!visited[y - 2][x]) {//up
				neighbours.push_back(0);
			}
		}
		if (y + 3 < row) {
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
			gotoxy(road_x_width * prex, prey);
			SetColor(road_color);
			cout << road;
			gotoxy(road_x_width * x, y);
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
				gotoxy(road_x_width * x, y - 1);
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
				gotoxy(road_x_width * x, y + 1);
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
				gotoxy(road_x_width * (x - 1), y);
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
				gotoxy(road_x_width * (x + 1), y);
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

void SetColor(int color)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


pair<COORD, COORD> choose_dot(){
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(h, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	DWORD cc;
	INPUT_RECORD irec;
	KEY_EVENT_RECORD key;
	MOUSE_EVENT_RECORD mouse;
	SetColor();
	COORD A = { -1,-1 }, B = {-1,-1};//source , dest
	while (A.X==-1 || A.Y==-1 || B.X==-1 || B.Y == -1) {
		ReadConsoleInput(h, &irec, 1, &cc);
		if (irec.EventType == MOUSE_EVENT)
		{
			mouse = (MOUSE_EVENT_RECORD&)irec.Event;
			switch (mouse.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED:
				//std::cout << "mouse left click" << std::endl;
				//std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
				if (A.X == -1 || A.Y == -1) {
					A.X = mouse.dwMousePosition.X / road_x_width;
					A.Y = mouse.dwMousePosition.Y;
					if (A.X == B.X && A.Y==B.Y) {
						A.X = -1;
						A.Y = -1;
					}
					else {
						gotoxy(A.X * road_x_width,A.Y);
						SetColor(source_dot_color);
						cout << the_road;
					}
				}
				else {
					B.X = mouse.dwMousePosition.X / road_x_width;
					B.Y = mouse.dwMousePosition.Y;
					if (A.X == B.X && A.Y == B.Y) {
						B.X = -1;
						B.Y = -1;
					}
					else {
						gotoxy(B.X * road_x_width, B.Y);
						SetColor(dest_dot_color);
						cout << the_road;
					}
				}
				break;
			//case RIGHTMOST_BUTTON_PRESSED:
			//	std::cout << "mouse right click" << std::endl;
			//	std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
			//	break;
			//case FROM_LEFT_2ND_BUTTON_PRESSED:
			//	std::cout << "mouse middle click" << std::endl;
			//	std::cout << "   mouse pos:" << mouse.dwMousePosition.X << " " << mouse.dwMousePosition.Y << std::endl;
			//	break;
			default:
				break;
			}

			switch (mouse.dwEventFlags)
			{
			case DOUBLE_CLICK:
				//std::cout << "mouse DOUBLE_CLICK" << std::endl;
				if (A.X == (mouse.dwMousePosition.X / road_x_width) && A.Y == (mouse.dwMousePosition.Y)) {
					A.X = -1;
					A.Y = -1;
					gotoxy(A.X * road_x_width, A.Y);
					SetColor(road_color);
					cout << the_road;
				}
				else if (B.X == (mouse.dwMousePosition.X / road_x_width) && B.Y == (mouse.dwMousePosition.Y)) {
					B.X = -1;
					B.Y = -1;
					gotoxy(B.X * road_x_width, B.Y);
					SetColor(road_color);
					cout << the_road;
				}
				break;
			//case MOUSE_WHEELED:
			//	std::cout << "mouse MOUSE_WHEELED:" << HIWORD(mouse.dwButtonState) << std::endl;
			//	break;
			default:
				break;
			}
		}
	}
	return make_pair(A,B);
}