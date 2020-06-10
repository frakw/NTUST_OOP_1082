#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <map>
#include <set>
#include <ctime>
#include <cmath>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <memory.h>
#include <algorithm>
#include <conio.h>
#include <regex>
#include <iomanip>
#include "Coord.h"
#include "basic.h"
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include "a_star_path.h"
#include "read_file.h"
#include "Input.h"
#include "enum.h"
//提示輸入，註解掉就沒有提示
//#define prompt

#ifdef prompt
#define prompt_input(output) cout<< output <<endl
#else
#define prompt_input(output)
#endif

//cmd輸入，註解掉改為黑視窗輸入
#define command_line

#define mygetline(cin,input)  if(cin.eof()){cin.clear();} getline(cin, input);
#define mydelete(ptr) do{if(ptr!=nullptr){delete[] ptr;ptr = nullptr;}}while(0)
#define mydelete_single(ptr) do{if(ptr!=nullptr){delete ptr;ptr = nullptr;}}while(0)
#define delete_2d(ptr,row) do{if(ptr!=nullptr){for(int __i=0;__i<row;__i++){delete[] ptr[__i];}delete[] ptr;ptr=nullptr;}}while(0)
#define self_assign_err_handle(input) do{if(this==&input)return;}while(0)
#define no_path_found -87
#define member_assign(a,b,member) (((a).(member)) = ((b).(member)))

using namespace std;
bool creature_order_compare(const Creature * const&a,const Creature * const&b);//生物與生物比較行動先後，可傳入怪物或角色

#ifdef DEBUG
#define AUTOEXT
#else
#define AUTOEXT  extern
#endif
AUTOEXT  int debug_mode;
#undef AUTOEXT

struct Race{//怪物種類
	string name;
	vector<Monster*> member;
	int card_number = -1;
	void choose_card();
	void round_end();
};

class Gloom_Haven {//遊戲主體class
public:
	Gloom_Haven();
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input);//tuple依序為全部角色陣列的頭指標，角色數量，全部怪物陣列的頭指標，怪物數量，地圖指標
	~Gloom_Haven();
	void set(tuple<Character*, int, Monster*, int, Map*> input);
	
	void start();//主要流程都在這裡
	
	int character_remain();//角色剩餘數
	int monster_remain();//怪物剩餘數
	int choose_remain();//剩餘幾個角色未選牌或長休

	void add_to_group(Monster*);//新增生物指標到 所有怪物種類的vector
	int monster_race_amount(string);//回傳該種類怪物場上剩餘數，滅絕則該回合debug mode卡牌編號不加1
	bool monster_race_in_discard(string,int);//該種類怪物的int編號卡牌是否在棄牌堆裡
private:
	Creature** all = nullptr;//所有角色與怪物指標排序後存放區，初始化時，先角色再怪物

	Map* map = nullptr;//地圖指標

	Character* character = nullptr;//角色陣列頭指標
	int character_amount=0;//角色陣列數量

	Monster* monster = nullptr;//怪物陣列頭指標
	int monster_amount = 0;//怪物陣列數量

	vector<Race> all_group;//所有怪物種類的vector
};