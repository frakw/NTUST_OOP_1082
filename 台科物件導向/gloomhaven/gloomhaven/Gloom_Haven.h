#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <utility>
#include "Coord.h"//先後順序要對
#include "basic.h"//先後順序要對
#include "Character.h"//先後順序要對
#include "Monster.h"//先後順序要對
#include "Map.h"//先後順序要對
#include "read_file.h"//先後順序要對

using namespace std;

//筆記: 怪物每輪出一張牌，角色每輪出二張牌，選一張當敏捷值
class Gloom_Haven {
public:
	Gloom_Haven();
	Gloom_Haven(bool mode);
	Gloom_Haven(tuple<Character*, Monster*, Map*> input, bool mode);
	~Gloom_Haven();
	void seiting(tuple<Character*, Monster*, Map*> input, bool mode);
	void start();//main process
	void stop();
private:
	bool DEBUG_MODE = false;
	Map* map = nullptr;
	Character* player = nullptr;
	int character_amount;
	Monster* enemy = nullptr;
	int enemy_amount;
};
