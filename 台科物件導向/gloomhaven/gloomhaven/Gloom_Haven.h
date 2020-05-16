#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <utility>
#include <memory.h>
#include <algorithm>
#include "Coord.h"//先後順序要對
#include "basic.h"//先後順序要對
#include "Character.h"//先後順序要對
#include "Monster.h"//先後順序要對
#include "Map.h"//先後順序要對
#include "read_file.h"//先後順序要對

//提示輸入
#define prompt_input 

using namespace std;

//筆記: 怪物每輪出一張牌，角色每輪出二張牌，選第一張當敏捷值
//攻擊可穿過障礙物
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(bool mode);
	Gloom_Haven(tuple<Character*,int, Monster*,int, Map*> input, bool mode);
	~Gloom_Haven();
	void seiting(tuple<Character*, int, Monster*, int, Map*> input, bool mode);
	void start();//main process
	void stop();
	int character_remain();//角色剩餘數
	int monster_remain();//怪物剩餘數
private:
	Creature** all = nullptr;//所有角色與怪物存放區(方便敏捷值排序用)，先角色再怪物

	bool DEBUG_MODE = false;
	Map* map = nullptr;
	Character* character = nullptr;
	int character_amount=0;
	//int character_remain = 0;//角色剩餘數

	Monster* monster = nullptr;
	int monster_amount = 0;
	//int monster_remain =0;//怪物剩餘數
};
