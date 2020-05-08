#include <iostream>
#include <string>
#include "dungeon.h"
#include <windows.h>
#include <cstdio>
#include <thread>
#include <ctime>
#include <cstdlib>
#include <cmath>
#include <iomanip>
#include <conio.h>
using namespace std;
bool now_draw = false;
bool now_update = false;
//void gotoxy(int , int);
void SetColor(int);
bool check_enemy_near(Creature*);
void DelLine(int y);//刪除整行
void Map::create(int W = 10,int H = 10,string Wall = "█") {
	static bool have_been_create = false;

	if (have_been_create) {
		for (int i = 0; i < h; ++i) {
			delete[] barrier[i];
		}
		delete[] barrier;
		ball.clear();//刪除場上的球
	}
	w = W;
	h = H;
	wall = Wall;
	barrier = new int* [h];
	for (int i = 0; i < h; ++i) {
		barrier[i] = new int[w];
		if (i == 0 || i == h - 1) {
			for (int j = 0;j < w;j++) {
				barrier[i][j] = 1;
			}
		}
		else {
			for (int j = 0;j < w;j++) {
				if (j == 0 || j == w - 1) {
					barrier[i][j] = 1;
				}
				else {
					barrier[i][j] = 0;
				}
			}
		}
	}
	if (have_been_create) {
		for (int i = 0;i < life.size();i++) {//重新分配隨機位置給已經存在的生物
		start:
			life[i]->x = rand() % (w - 2) + 1;
			life[i]->y = rand() % (h - 2) + 1;
			if (!barrier[life[i]->y][life[i]->x]) {
				barrier[life[i]->y][life[i]->x] = 1 + life[i]->team_number;
				life[i]->direction = rand() % 4;
			}
			else {
				goto start;
			}
		}
	}
	have_been_create = true;
}
void Map::add_creature(Creature* a) {
	start:
	a->x = rand() % (w -2) +1;
	a->y = rand() % (h -2) +1;
	if (!barrier[a->y][a->x]) {
		barrier[a->y][a->x] = 1 + a->team_number;
		a->direction = rand() % 4;
		life.push_back(a);
	}
	else {
		goto start;
	}
}

void Map::die_creature(int index) {
	
	if (index < life.size() && index) {//不可刪除玩家
		life[index]->clear();
		barrier[life[index]->y][life[index]->x] = 0;
		delete []life[index];//將此怪物的記憶體釋放
		DelLine(h + life.size() + 1);//刪除血條那行
		life.erase(life.begin() + index);
	}
	else {//game over not complete
		system("cls");
		cout << "  _____          __  __ ______    ______      ________ _____  \n";
		cout << " / ____|   /\\   |  \\/  |  ____|  / __ \\ \\    / /  ____|  __ \\ \n";
		cout << "| |  __   /  \\  | \\  / | |__    | |  | \\ \\  / /| |__  | |__) |\n";
		cout << "| | |_ | / /\\ \\ | |\\/| |  __|   | |  | |\\ \\/ / |  __| |  _   / \n";
		cout << "| |__| |/ ____ \\| |  | | |____  | |__| | \\  /  | |____| | \\ \\ \n";
		cout << " \\_____/_/    \\_\\_|  |_|______|  \\____/   \\/   |______|_|  \\_\\\n";
		Sleep(1000);
		cout << "Want play again? [y/n]";
		while (1) {
			if (GetAsyncKeyState('y') || GetAsyncKeyState('Y')) {
				system("cls");
				ball.clear();
				del_all_creature();
				init_creature(1);
				draw();
				break;
			}
			else if (GetAsyncKeyState('n') || GetAsyncKeyState('N')) {
				exit(1);
			}
		}
	}
}

void Map::draw() {
	if (!now_draw) {
		now_draw = true;
		gotoxy(0, 0);
		for (int i = 0;i < h;i++) {
			for (int j = 0;j < w;j++) {
				if (!barrier[i][j]) {
					cout << "  ";
				}
				else {
					cout << wall;
				}
			}
			cout << '\n';
		}
		now_draw = false;
	}
}

void Map::set(int x,int y,string change) {//not compelete
	gotoxy((x + 1) * 2, y + 1);
	cout << change;
}


void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}


void Creature::set_pos(int X,int Y) {
	//if (X < max_x) x = X;
	//if (Y < max_y) y = Y;
}

Ball Creature::attack() {
	Ball ball;
	ball.power = power;
	ball.x = x;
	ball.y = y;
	switch (direction) {
	case 0: ball.y = y - 1;break;
	case 1: ball.y = y + 1;break;
	case 2: ball.x = x - 1;break;
	case 3: ball.x = x + 1;break;
	}
	ball.direction = direction;
	attack_time = clock();
	return ball;
}

void Creature::show() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	gotoxy(x * 2, y );
	cout << (string)(emission_status ? attack_icon[direction] : icon[direction]);
	gotoxy(0, 0);
}

void Creature::clear() { 
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	gotoxy(x * 2, y);
	cout << "  ";
	gotoxy(0, 0);
}

void Map::creature_attacked(int index) {
	ball.push_back(life[index]->attack());
	int temp=ball.size() - 1;
}
void Map::attack_animate(int index) {
	life[index]->emission_status = true;
	Sleep(200);
	life[index]->emission_status = false;
}
void Map::ball_moved(int index) {
	if (barrier[ball[index].y][ball[index].x] == 1) {
		ball.erase(ball.begin() + index);
		return;
	}
	else if (barrier[ball[index].y][ball[index].x] > 1) {
		for (int i = 0;i < life.size();i++) {
			if (life[i]->x == ball[index].x && life[i]->y == ball[index].y) {
				life[i]->hp -= ball[index].power;
				ball[index].clear();
				ball.erase(ball.begin() + index);
				if (life[i]->hp <= 0) {
					die_creature(i);
				}
				return;
			}
		}
	}
	if (!ball[index].latest_move) {//初始化
		ball[index].latest_move = clock();
		ball[index].show();
		return;
	}
	if (clock() - ball[index].latest_move < ball[index].delay) {
		return;
	}
	coord next = { ball[index].x,ball[index].y };
	switch (ball[index].direction) {
	case 0:next.y -= 1;break;
	case 1:next.y += 1;break;
	case 2:next.x -= 1;break;
	case 3:next.x += 1;break;
	}

	if (barrier[next.y][next.x] == 0) {
			ball[index].clear();
			ball[index].x = next.x;
			ball[index].y = next.y;
			ball[index].show();
			ball[index].latest_move = clock();
	}
	else if (barrier[next.y][next.x] > 1) {
		for (int i = 0;i < life.size();i++) {
			if (life[i]->x == next.x && life[i]->y == next.y) {
				life[i]->hp -= ball[index].power;
				ball[index].clear();
				ball.erase(ball.begin() + index);
				if (life[i]->hp <= 0) {
					die_creature(i);
				}
				return;
			}
		}
	}
	else {
		ball[index].clear();
		ball.erase(ball.begin() + index);
		return;
	}
}

void Map::update_creature_status() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	if (!now_update) {
		now_update = true;
		//static int pre_life_amount=-1;
		//if (pre_life_amount != life.size()) {
		//	system("cls");
		//	draw();
		//	pre_life_amount = life.size();
		//}
		for (int i = 0;i < life.size();i++) {
			if (life[i]->this_turn_attack) {
				life[i]->this_turn_attack = false;
				continue;
			}
			int start_x, start_y;
			int end_x, end_y;
			start_x = (life[i]->x - 4 >= 1) ? life[i]->x - 4 : 1;
			start_y = (life[i]->y - 4 >= 1) ? life[i]->y - 4 : 1;
			end_x = (life[i]->x + 4 <= (w-2)) ? life[i]->x + 4 : (w - 2);
			end_y = (life[i]->y + 4 <= (h-2)) ? life[i]->y + 4 : (h - 2);
			for (int j=start_y;j <= end_y;j++) {
				for (int k = start_x;k <= end_x;k++) {
					if ((barrier[j][k] > 1) && ((barrier[j][k] - 2) != life[i]->team_number)) {
						for (int g = i + 1;g < life.size();g++) {
							if (life[g]->y == j && life[g]->x == k) {
								life[g]->enemy_x = life[i]->x;
								life[g]->enemy_y = life[i]->y;
								life[g]->attack_status = true;
								life[g]->this_turn_attack = true;
								break;
							}
						}
						life[i]->enemy_x = k;
						life[i]->enemy_y = j;
						life[i]->attack_status = true;
						goto out;//跳出巢狀迴圈
					}
					else {
						life[i]->attack_status = false;
					}
				}
			}
		out:;
			life[i]->this_turn_attack = false;
		}
		for (int i = 0;i < ball.size();i++) {
			ball_moved(i);
		}
		gotoxy(0, h);
		cout << '\n' << "Creature :" << '\n';
		for (int i = 0;i < life.size();i++) {
			cout <<right<< setw(10) << (string)(life[i]->attack_status ? life[i]->attack_icon[life[i]->direction] : life[i]->icon[life[i]->direction]);
			cout << setw(10) << life[i]->name;
			int blood_count = ceil(((double)life[i]->hp / (double)life[i]->full_hp) * 10);
			cout <<fixed<< setprecision(0) << "  HP: " << left << setw(5) << life[i]->hp << "[";
			//printf("  HP: %.0f%% [", (double)life[i]->hp / (double)life[i]->full_hp * (double)100);
			for (int j = 0; j < blood_count;j++) {
				cout << "█";
			}
			for (int j = 0; j < ((10 - blood_count)>10?10:(10 - blood_count));j++) {
				cout << "  ";
			}
			cout << "]  position x:" << left << setw(5) << life[i]->x  << "y:" << left << setw(5) << life[i]->y  << "power:" << left << setw(5) << life[i]->power << "   " << '\n';
		}
		for (int k = 0;k < life.size();k++) {
			life[k]->show();
		}
		now_update = false;
	}
}


void Map::random_run(int index) {
start:
	life[index]->direction = rand() % 4;
	int i = 0;
	while (!creature_moved(index)) {
		if (i > 3) {
			barrier[life[index]->y][life[index]->x] = 0;
			life[index]->clear();
			life[index]->x = rand() % (w - 2) + 1;
			life[index]->y = rand() % (h - 2) + 1;
			if (!barrier[life[index]->y][life[index]->x]) {
				barrier[life[index]->y][life[index]->x] = 1 + life[index]->team_number;
				return;
			}
			else {
				goto start;
			}
		}
		life[index]->direction = rand() % 4;
		i++;
	}
}

bool Map::creature_moved(int index) {
	if (clock() - life[index]->attack_time < life[index]->cd_time) {
		return true;
	}
	if (life[index]->destination.x == life[index]->x && life[index]->destination.y == life[index]->y) {
		life[index]->direction = life[index]->destination.dir;
		life[index]->destination = { -1,-1 };
		creature_attacked(index);
		return true;//強制結束
	}
	int now_x = life[index]->x;
	int now_y = life[index]->y;
	for (int i = 0;i < life[index]->speed;i++) {
		switch (life[index]->direction) {
		case 0: {
			if (!barrier[now_y - 1][now_x]) {
				life[index]->clear();
				life[index]->y -= life[index]->speed;
				barrier[now_y - 1][now_x] = 2 + life[index]->team_number;
			}
			else { return false; }
			break;
		}
		case 1: {
			if (!barrier[now_y + 1][now_x]) {
				life[index]->clear();
				life[index]->y += life[index]->speed;
				barrier[now_y + 1][now_x] = 2 + life[index]->team_number;
			}
			else { /*life[index]->show();*/ return false; }
			break;
		}
		case 2: {
			if (!barrier[now_y][now_x - 1]) {
				life[index]->clear();
				life[index]->x -= life[index]->speed;
				barrier[now_y][now_x - 1] = 2 + life[index]->team_number;
			}
			else {/* life[index]->show();*/ return false; }
			break;
		}
		case 3: {
			if (!barrier[now_y][now_x + 1]) {
				life[index]->clear();
				life[index]->x += life[index]->speed;
				barrier[now_y][now_x + 1] = 2 + life[index]->team_number;
			}
			else { /*life[index]->show();*/ return false; }
			break;
		}

		}
	}
	life[index]->show();
	barrier[now_y][now_x] = 0;

	return true;
}


void special_map(int** map) {
	//draw the map
}

void Map::attack_run(int index) {
	if (life[index]->destination.x != -1) {
		if (!creature_moved(index)) {
			life[index]->destination = { -1,-1 };
			life[index]->attack_status = false;//到不了就放棄
		}
		return;
	}
	int x_dis = life[index]->x - life[index]->enemy_x, y_dis = life[index]->y - life[index]->enemy_y;
	if (x_dis == 0) {
		life[index]->direction = (int)(y_dis > 0 ? dir::up : dir::down);
		life[index]->destination.dir = life[index]->direction;
		if ((clock() - life[index]->attack_time) > life[index]->cd_time) {
			ball.push_back(life[index]->attack());
		}
		return;
	}
	else if (y_dis == 0) {
		life[index]->direction = (int)(x_dis > 0 ? dir::left : dir::right);
		life[index]->destination.dir = life[index]->direction;
		if ((clock() - life[index]->attack_time) > life[index]->cd_time) {
			ball.push_back(life[index]->attack());
		}
		return;

	}
	else if (abs(x_dis) <= abs(y_dis)) {
			life[index]->direction = x_dis > 0 ? 2 : 3;
			life[index]->destination = { life[index]->enemy_x,life[index]->y ,(int)(y_dis > 0 ? dir::up : dir::down) };
	}
	else {
		life[index]->direction = y_dis > 0 ? 0 : 1;
		life[index]->destination = { life[index]->x ,life[index]->enemy_y,(int)(x_dis > 0 ? dir::left : dir::right)};
	}
	creature_moved(index);
}

void DelLine(int y){//刪除整行
	HANDLE    hOutput;
	CONSOLE_SCREEN_BUFFER_INFO    sbi;
	DWORD    len, nw;
	COORD    cd = { 0, y };
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hOutput, &sbi);
	len = sbi.dwSize.X;
	FillConsoleOutputCharacter(hOutput, _T(' '), len, cd, &nw);
}

void Creature::set_icon(string a,string b,string c,string d) {
	icon[0] = a;
	icon[1] = b;
	icon[2] = c;
	icon[3] = d;
}
void Creature::set_attack_icon(string a, string b, string c, string d) {
	attack_icon[0] = a;
	attack_icon[1] = b;
	attack_icon[2] = c;
	attack_icon[3] = d;
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void Map::init_creature(int monster_amount) {
	srand(time(NULL));
	/*英雄初始化區----------------------------*/
	add_creature(new Creature[1]);
	life[0]->name = "hero";
	life[0]->team_number = 1;
	life[0]->set_icon("↑", "↓", "←", "→");
	life[0]->set_attack_icon("︽", "︾", "《", "》");
	life[0]->cd_time = 1000;
	life[0]->speed = 1;
	/*----------------------------------------*/
	for (int i = 0;i < monster_amount;i++) {
		/*第一隻怪物初始化區(預設有一隻怪)----------*/
		add_creature(new Creature[1]);//預設一隻怪物
		life[i+1]->name = "monster" + to_string(life.size() - 1);
		life[i+1]->team_number = 0;//設為敵方
	}
	/*-----------------------------------------*/
}

void Map::del_all_creature() {
	int index = life.size() - 1;
	for (;index>=0;index--) {
		life[index]->clear();
		barrier[life[index]->y][life[index]->x] = 0;
		delete[]life[index];//將此怪物的記憶體釋放
		DelLine(h + life.size() + 1);//刪除血條那行
		life.erase(life.begin() + index);
	}
}