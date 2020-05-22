
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
#include <fstream>
#include <string>	
#include <vector>
#include <stack>
#include <ctime>
#include <cmath>
#include <set>
#include<windows.h>
#include<conio.h>
#include <tuple>
#include <list>
#include <algorithm>
using namespace std;
class Maze;
#define the_road "  "
#define the_wall "█"
#define road_color 55
#define wall_color 7
#define dot_color 160
#define road_x_width 2
#define source_dot_color 155
#define dest_dot_color 75
void gotoxy(int xpos, int ypos);
void SetColor(int color = 7);
pair<COORD, COORD> choose_dot(Maze& maze);
void A_star_path(Maze maze, pair< COORD, COORD > coord);
//test xy : 117 60
class Maze {
public:
	Maze() {
		row = 10;
		col = 10;
	}
	Maze(int, int);
	Maze(const Maze& a) {
		*this = a;
	}
	~Maze();

	void create(bool, time_t delay);
	bool** maze_01()const{
		return map;
	}
	bool map_xy(int x,int y) {
		if (x >= col || x < 0 || y >= row || y < 0) {
			return false;
		}
		return map[y][x];
	}
	bool map_xy(COORD a) {
		if (a.X >= col || a.X < 0 || a.Y >= row || a.Y < 0) {
			return false;
		}
		return map[a.Y][a.X];
	}
	bool& map_xy_ref(COORD a) {
		return map[a.Y][a.X];
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
	Maze& operator=(const Maze& a){
		if (a.visited == nullptr || a.map == nullptr) {//fail
			this->~Maze();
			visited = nullptr;
			map = nullptr;
			return *this;
		}
		if (visited != nullptr || map != nullptr) {
			this->~Maze();
		}
		this->new_memory(a.col,a.row);
		for (int i = 0;i < row;i++) {
			for (int j = 0;j < col;j++) {
				map[i][j] = a.map[i][j];
				visited[i][j] = a.visited[i][j];
			}
		}
		return *this;
	}
	int return_row() const{
		return row;
	}
	int return_col() const{
		return col;
	}
private:
	string road = the_road;
	string wall = the_wall;//¢i
	bool new_memory(int, int);
	int row = 10;
	int col = 10;
	bool** visited = nullptr;//*****visited刪除*****
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
	while (1) {
		A_star_path(maze, choose_dot(maze));
		SetColor();
		gotoxy(0, 0);
		_getch();
		maze.print();
	}
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
		else {
			for (int j = 0;j < col;j += 2) {
				map[i][j] = 1;
				//visited[i][j] = true;
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
	if (!new_memory(col, row)) {
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
				SetColor();
				cout << wall;
			}
			else {
				SetColor(road_color);
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


pair<COORD, COORD> choose_dot(Maze& maze) {
	HANDLE h = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(h, ENABLE_EXTENDED_FLAGS | ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	DWORD cc;
	INPUT_RECORD irec;
	KEY_EVENT_RECORD key;
	MOUSE_EVENT_RECORD mouse;
	SetColor();
	COORD A = { -1,-1 }, B = { -1,-1 };//source , dest
	while (1) {
		ReadConsoleInput(h, &irec, 1, &cc);
		if (irec.EventType == MOUSE_EVENT)
		{
			mouse = (MOUSE_EVENT_RECORD&)irec.Event;
			switch (mouse.dwButtonState)
			{
			case FROM_LEFT_1ST_BUTTON_PRESSED:{
				if (A.X == -1 || A.Y == -1) {
					A.X = mouse.dwMousePosition.X / road_x_width;
					A.Y = mouse.dwMousePosition.Y;
					if ((A.X == B.X && A.Y == B.Y) || maze.map_xy(A.X, A.Y)) {
						A.X = -1;
						A.Y = -1;
					}
					else {
						gotoxy(A.X * road_x_width, A.Y);
						SetColor(source_dot_color);
						cout << the_road;
					}

				}
				else if (B.X == -1 || B.Y == -1) {
					B.X = mouse.dwMousePosition.X / road_x_width;
					B.Y = mouse.dwMousePosition.Y;
					if ((A.X == B.X && A.Y == B.Y) || maze.map_xy(B.X, B.Y)) {
						B.X = -1;
						B.Y = -1;
					}
					else {
						gotoxy(B.X * road_x_width, B.Y);
						SetColor(dest_dot_color);
						cout << the_road;
					}
				}
			}break;
			case RIGHTMOST_BUTTON_PRESSED: {
				COORD tmp = { (mouse.dwMousePosition.X / road_x_width) ,(mouse.dwMousePosition.Y) };
				if ((maze.return_col()-1) > tmp.X && (maze.return_row()-1) > tmp.Y && tmp.X > 0 && tmp.Y > 0) {
					maze.map_xy_ref(tmp) = !maze.map_xy_ref(tmp);
					gotoxy(tmp.X * road_x_width, tmp.Y);
					if (maze.map_xy_ref(tmp)) {
						SetColor(wall_color);
						cout << the_wall;
					}
					else {
						SetColor(road_color);
						cout << the_road;
					}
					Sleep(50);
				}
			}
			default:
				break;
			}

			switch (mouse.dwEventFlags)
			{
			case DOUBLE_CLICK: {
				if (A.X == (mouse.dwMousePosition.X / road_x_width) && A.Y == (mouse.dwMousePosition.Y)) {

					gotoxy(A.X * road_x_width, A.Y);
					SetColor(road_color);
					cout << the_road;
					A.X = -1;
					A.Y = -1;
				}
				else if (B.X == (mouse.dwMousePosition.X / road_x_width) && B.Y == (mouse.dwMousePosition.Y)) {
					gotoxy(B.X * road_x_width, B.Y);
					SetColor(road_color);
					cout << the_road;
					B.X = -1;
					B.Y = -1;
				}
			}
				break;
			default:
				break;
			}
		}
		else if (irec.EventType == KEY_EVENT)
		{
			key = (KEY_EVENT_RECORD&)irec.Event;
			if (key.bKeyDown)
			{
				if (key.wVirtualKeyCode == VK_RETURN && A.X!=-1 && A.Y != -1 && B.X != -1 && B.Y != -1) {//enter鍵
					break;
				}
			}
		}
		gotoxy(0, 0);
	}
	return make_pair(A, B);
}

class Grid {
public:
	COORD self;
	Grid* father = nullptr;
	int F=0;
	int G=0;
	int H=0;
	Grid(COORD in,Grid* the_father,COORD end_point){
		this->self = in;
		if (the_father != nullptr) {
			this->calc_val(the_father, end_point);
		}
	}
	void calc_val(Grid* the_father,COORD end_point)	{
		int tmp = abs(the_father->self.X - self.X) + abs(the_father->self.Y - self.Y);
		if (father==nullptr) {
			this->father = the_father;
			G = father->G + tmp;
			H = abs(end_point.X - self.X) + abs(end_point.Y - self.Y);
			F = G + H;
		}
		else {
			if (tmp < G) {
				this->father = the_father;
				G = father->G + tmp;
				F = G + H;
			}
		}
	}

};

int exist_in(vector<Grid*>* data_ptr, COORD check);

void A_star_path(Maze maze, pair< COORD, COORD > coord) {
	vector<Grid*> close_list;//不可以用vector<Grid>，因為指標Grid*不可以指向vector中的元素
	vector<Grid*> open_list;//不可以用vector<Grid>，因為指標Grid*不可以指向vector中的元素
	Grid* current = new Grid(coord.first,nullptr,coord.second);
	open_list.push_back(current);	
	do {
		if (open_list.empty()) {
			gotoxy(0,maze.return_row());
			SetColor();
			cout << "no path find";
			Sleep(2000);
			gotoxy(0, maze.return_row());
			cout << "            ";
			return;
		}
		int min = open_list[0]->F;
		int pos = 0 ;
		for (int i = 1;i < open_list.size();i++){
			if (open_list[i]->F < min) {
				pos = i;
				min = open_list[i]->F;
			}
		}
		close_list.push_back(open_list[pos]);
		open_list.erase(open_list.begin()+pos);
		current = close_list[close_list.size() - 1];
		int tmpX = current->self.X;
		int tmpY = current->self.Y;
		COORD direction[4] = { { tmpX,tmpY - 1 },{ tmpX,tmpY + 1 },{tmpX - 1,tmpY },{tmpX + 1,tmpY } };
		for (int i = 0;i < 4;i++) {
			if (exist_in(&close_list, direction[i])==-1 && !maze.map_xy(direction[i])) {
				int pos2 = exist_in(&open_list, direction[i]);
				if (pos2==-1) {
					Grid* tmp = new Grid(direction[i], current, coord.second);
					open_list.push_back(tmp);
				}
				else {
					open_list[pos2]->calc_val(current,coord.second);
				}
			}
		}
	} while ((current->self.X != coord.second.X) || (current->self.Y != coord.second.Y));
	current = current->father;
	while (current->father!=nullptr){
		gotoxy(current->self.X * road_x_width, current->self.Y);
		SetColor();
		cout << the_road;
		current = current->father;
	}
}

int exist_in(vector<Grid*>* data_ptr,COORD check) {
	for (int i = 0;i < data_ptr->size();i++) {
		if ((*data_ptr)[i]->self.X == check.X && (*data_ptr)[i]->self.Y == check.Y) {
			return i;
		}
	}
	return -1;
}