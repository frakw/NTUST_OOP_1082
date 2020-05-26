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
#include "Coord.h"//先後順序要對
#include "basic.h"//先後順序要對
#include "Character.h"//先後順序要對
#include "Monster.h"//先後順序要對
#include "Map.h"//先後順序要對
#include "read_file.h"//先後順序要對
#include "Input.h"
//提示輸入
#define prompt_input 

using namespace std;

//筆記: 怪物每輪出一張牌，角色每輪出二張牌，選第一張當敏捷值
//攻擊可穿過障礙物
//待解決:敏捷值排序
//待做: discard改hand,採用macro coord_in提升可讀性, regex ,choose_card改virtual 
//採用nullcoord 與 == coord creature die funtion
//macro庫，集中管理遊戲輸出訊息
//cout與txt檔同時輸出
//input output 包裝成class可任意更改輸入或輸出，也可多個輸出
//提示輸入訊息
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
	Creature** all = nullptr;//所有角色與怪物排序後存放區，初始化時，先角色再怪物

	bool DEBUG_MODE = false;
	Map* map = nullptr;

	Character* character = nullptr;
	int character_amount=0;

	Monster* monster = nullptr;
	int monster_amount = 0;
};