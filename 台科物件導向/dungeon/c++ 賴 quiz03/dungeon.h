#ifndef _DUNGEON_H
#define _DUNGEON_H
#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <thread>
#include <tchar.h>//刪除整行 用到的函式庫
#include <windows.h>
using namespace std;

//已知bug:hero一開始是攻擊狀態
/*待做:
1.修正怪物攻擊移動模式
2.緩衝區關閉
3.迷宮生成
4.檔案紀錄(地圖，玩家，怪物)
5.子彈互撞抵銷
6.#define team_kill
7.玩家移動效果
8.射擊時變換icon
9.log誰做了甚麼，誰死了...
10.子彈爆炸效果
11.等級系統
12.關卡系統
13.選單系統
14.陷阱
15.增強物品
*/
void gotoxy(int xpos, int ypos);
enum class dir:int {
	up, down, left, right
};

typedef struct _coord {
	int x;
	int y;
	int dir;
}coord;

class Ball{
public:
	int x=1;
	int y=1;
	int direction;
	time_t latest_move = 0;
	time_t delay=50;
	string contain = "●";
	int power=10;
	void show() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(0);
		gotoxy(x * 2, y);
		cout << contain;
		gotoxy(0, 0);
	}
	void clear() {
		std::ios::sync_with_stdio(false);
		std::cin.tie(0);
		gotoxy(x * 2, y);
		cout << "  ";
		gotoxy(0, 0);
	}
};

class Creature {
public:
	//bool move();//朝direction的方向前進 移動成功回傳true 反之
	void show();//印出此creature
	void clear();
	void set_pos(int,int);
	void set_icon(string,string,string,string);
	void set_attack_icon(string,string,string,string);
	Ball attack();//朝direction的方向攻擊
	//void be_attacked(char);//被direction的方向攻擊
	int x=0, y=0;
	string name;
	
	string icon[4] = { " ^", " v", " <", " >" }, attack_icon[4] = { " ^", " v", " <", " >" };//︾《》︽ 發射時變為attack icon
	int hp=100,full_hp=100;//現在血量 滿血血量
	int power = 10;//攻擊力
	bool attack_status=false;//攻擊狀態
	bool emission_status = false;//發射狀態
	int vision_range = 4;//視力範圍
	int speed = 1;//每次移動距離
	int direction = 1;//方向
	int team_number = 1;//隊伍編號 壞人陣營為0 好人陣營為1 
	int enemy_x, enemy_y;//一次鎖定一個敵人，敵人的x y 
	bool this_turn_attack = false;//\這回合已進入攻擊狀態
	coord destination = {-1,-1};//目的地座標，無目的則為-1
	time_t attack_time = 0;//上次攻擊時間
	time_t cd_time = 1000;//攻擊cd
};
class Map {
public:
	void create(int,int,string);
	void init_creature(int);//初始化hero與怪物，int是幾隻怪
	void add_creature(Creature*);
	void die_creature(int);//number of index creature died
	void del_all_creature();//刪除所有生物
	void draw();
	void set(int, int, string);//設定地圖中任xy為string
	void update_creature_status();
	void creature_attacked(int);
	bool creature_moved(int);
	void ball_moved(int);
	void random_run(int);
	void attack_run(int);
	void attack_animate(int);
	int** barrier;//not finished //0 空 1牆壁 2壞人 3好人 (2+隊伍編號)
	int w =10 , h =10;//地圖長寬
	string wall = "█";
	vector<Creature*> life;
	vector<Ball> ball;
	friend class Ball;
	friend class Creature;
};




const bool segment[10][9][3] = {
{{1,1,1},{1,0,1},{1,1,1}},//0
{{1,0,1},{0,0,1},{0,0,1}},//1
{{1,1,1},{0,1,1},{1,1,0}},//2
{{1,1,1},{0,1,1},{0,1,1}},//3
{{1,0,1},{1,1,1},{0,0,1}},//4
{{1,1,1},{1,1,0},{0,1,1}},//5
{{1,1,1},{1,1,0},{1,1,1}},//6
{{1,1,1},{1,0,1},{0,0,1}},//7
{{1,1,1},{1,1,1},{1,1,1}},//8
{{1,1,1},{1,1,1},{0,1,1}} //9
};
const char display[3][3] = {
  {' ','_',' '},
  {'|','_','|'},
  {'|','_','|'} };

#endif