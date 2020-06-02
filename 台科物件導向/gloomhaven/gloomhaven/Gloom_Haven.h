#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
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
#include "Coord.h"//先後順序要對
#include "basic.h"//先後順序要對
#include "Character.h"//先後順序要對
#include "Monster.h"//先後順序要對
#include "Map.h"//先後順序要對
#include "a_star_path.h"
#include "read_file.h"//先後順序要對
#include "Input.h"
//提示輸入，註解掉就沒有提示
//#define prompt

#ifdef prompt
#define prompt_input(output) cout<< output <<endl
#else
#define prompt_input(output)
#endif

#define mygetline(cin,input)  if(cin.eof()){cin.clear();} getline(cin, input);
#define mydelete(ptr) do{if(ptr!=nullptr){delete[] ptr;ptr = nullptr;}}while(0)
#define mydelete_single(ptr) do{if(ptr!=nullptr){delete ptr;ptr = nullptr;}}while(0)
#define delete_2d(ptr,row) do{if(ptr!=nullptr){for(int __i=0;__i<row;__i++){delete[] ptr[__i];}delete[] ptr;ptr=nullptr;}}while(0)
#define self_assign_err_handle(input) do{if(this==&input)return;}while(0)
using namespace std;

//待做:採用macro coord_in提升可讀性, regex
//採用nullcoord 與 == coord creature die funtion
//macro庫，集中管理遊戲輸出訊息
//cout與txt檔同時輸出
//input output 包裝成class可任意更改輸入或輸出，也可多個輸出
//提示輸入訊息

//資料封裝，self assign，註解
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input, bool mode);//tuple依序為全部角色陣列的頭指標，角色數量，全部怪物陣列的頭指標，怪物數量，地圖指標
	~Gloom_Haven();
	void set(tuple<Character*, int, Monster*, int, Map*> input, bool mode);
	
	void start();//主要流程都在這裡
	
	int character_remain();//角色剩餘數
	int monster_remain();//怪物剩餘數
	int choose_remain();//剩餘幾個角色未選牌或長休
private:
	Creature** all = nullptr;//所有角色與怪物指標排序後存放區，初始化時，先角色再怪物

	bool DEBUG_MODE = false;
	Map* map = nullptr;

	Character* character = nullptr;
	int character_amount=0;

	Monster* monster = nullptr;
	int monster_amount = 0;
};