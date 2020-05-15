#pragma once
#include "Coord.h"
#include <utility>
#include <string>
class Character;//不可include 標頭檔，會出現遺漏類型規範-假設為int
class Monster;//不可include 標頭檔，會出現遺漏類型規範-假設為int
using namespace std;

class Map {
public:
	Map();
	Map(int in_row, int in_col);
	~Map();
	void set(string input);
	int row=0, col=0;
	char** body = nullptr;
	Coord start_pos[4];//可選位置
	Character* player = nullptr;
	Monster* enemy = nullptr;
};