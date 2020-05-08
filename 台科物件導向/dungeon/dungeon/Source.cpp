#include <iostream>
#include <thread>
#include <windows.h>
#include <conio.h>
#include "dungeon.h"
#include <ctime>
#include <cstdlib>
#include <vector>
using namespace std;

bool stop= false;
Map map;
void segmentdisplay(int);//int版 開頭不可以是0
void DelLine(int y);//刪除整行
int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int i = 0;
	system("title WASD上下左右移動 ↑↓←→改變方向 接近會改變為攻擊狀態 ︽︾《》並搖擺  按 n 新增敵人");
	system("mode con cols=200 lines=150");
	/*教學-----------------------------*/
	//for (int j = 5;j >=0;j--) {
	//	cout << "WASD上下左右移動 ↑↓←→改變方向 接近會改變為攻擊狀態 ︽︾《》並搖擺  按 n 新增敵人" << endl;
	//	segmentdisplay(j);
	//	Sleep(1000);
	//	system("cls");
	//}
	/*----------------------------------*/
	system("cls");
	map.create(30, 20,"█");//////
	map.init_creature(1);//預設一隻怪
	srand(time(NULL));
	map.draw();//初始化地圖
	char in;
	string trash;
	while (1) {
		cin.clear();
		//switch (in) {
		//case 'w':case 'W': hero.direction = 0; hero.move();break;
		//case 'a':case 'A': hero.direction = 2; hero.move();break;
		//case 's':case 'S': hero.direction = 1; hero.move();break;
		//case 'd':case 'D': hero.direction = 3; hero.move();break;
		//case 72: hero.direction = 0; break;//方向鍵
		//case 75: hero.direction = 2; break;
		//case 80: hero.direction = 1; break;
		//case 77: hero.direction = 3; break;
		//case ' ':map.someone_attacked(0);break;
		//case 27://ESC
		//	stop = true; mthread.join(); system("pause"); return 0;
		//}
		if (GetAsyncKeyState(0x57)) {//w
			map.life[0]->direction = 0; map.creature_moved(0);
		}
		if (GetAsyncKeyState(0x53)) {//s
			map.life[0]->direction = 1; map.creature_moved(0);
		}
		if (GetAsyncKeyState(0x41)) {//a
			map.life[0]->direction = 2; map.creature_moved(0);
		}
		if (GetAsyncKeyState(0x44)) {//d
			map.life[0]->direction = 3; map.creature_moved(0);
		}
		//if (GetAsyncKeyState(0x4B)) {//進入攻擊狀態，按2次取消
		//	hero.attack_status = !hero.attack_status;
		//	Sleep(100);
		//}
		if (GetAsyncKeyState(0x4E)) {//n 新增monster
			map.add_creature(new Creature[1]);
			for (int i = 1;i < map.life.size();i++) {
				int j;
				for (j = 1;j < map.life.size();j++) {
					if ("monster" + to_string(i) == map.life[j]->name) {
						break;
					}
				}
				if (j == map.life.size()) {
					map.life[map.life.size() - 1]->name = "monster" + to_string(i);
				}
			}
			map.life[map.life.size() - 1]->team_number = 0;//設為敵方
			Sleep(20);
		}
		if (GetAsyncKeyState(0x4D)) {//m 刪除monster，從最後一隻開始
			if (map.life.size() - 1 != 0) {//不可刪除玩家
				map.die_creature(map.life.size() - 1);
				Sleep(20);
			}
		}
		if (GetAsyncKeyState(0x43)) {//c 重新印出地圖，破圖時使用
			system("cls");
			map.draw();
			//Sleep(100);
		}
		if (GetAsyncKeyState(0x50)) {//p 改變地圖大小，bug:有之前輸入的東西
			system("cls");
			int temp_x, temp_y;
			cout << "輸入地圖 長(y) 寬(x) :";
			cin >> temp_y >> temp_x;
			system("cls");
			map.create(temp_x, temp_y, "█");
			map.draw();
		}

		if (GetAsyncKeyState(0x26)) {
			map.life[0]->direction = 0;
		}
		if (GetAsyncKeyState(0x28)) {
			map.life[0]->direction = 1;
		}
		if (GetAsyncKeyState(0x25)) {
			map.life[0]->direction = 2;
		}
		if (GetAsyncKeyState(0x27)) {
			map.life[0]->direction = 3;
		}

		if (GetAsyncKeyState(VK_SPACE)) {//發射子彈
			map.ball.push_back(map.life[0]->attack());
			Sleep(30);
		}

		if (i == 4) {//每4*50毫秒 隨機移動一次

			for (int j = 1;j < map.life.size();j++) {
				if (!map.life[j]->attack_status) {
					map.random_run(j);
				}
				else {
					map.attack_run(j);
				}
			}

			i = 0;
		}
		Sleep(30);
		map.update_creature_status();
		i++;
	}
	system("pause");
	return 0;
}

void segmentdisplay(int a) {
	int i, j, g;
	int k[100], h = -1;
	if (!a) {
		k[0] = 0;
		h = 0;
	}
	while (a) {
		h++;
		k[h] = a % 10;
		a /= 10;
	}
	for (i = 0;i < 3;i++) {
		for (g = h;g >= 0;g--) {
			for (j = 0;j < 3;j++) {
				printf("%c", segment[k[g]][i][j] ? display[i][j] : ' ');
			}
			printf("%s", k[g - 1] != 1 && g ? " " : "");
		}
		printf("\n");
	}
}
