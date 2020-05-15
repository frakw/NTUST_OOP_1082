#pragma once
#include <string>
using namespace std;
class Creature;
class Monster : public Creature{
public:
	Monster();
	Monster(string in_name, int val, int in_damage, int in_range, bool in_elite);
	Monster& operator=(const Monster& input);
	void switch_status(int num);

	int damage=0;
	int range=0;//0為近戰怪
	bool elite = false; //是(true)否(false)為菁英
	bool show = true;//是(true)否(false)出現在場上
	int elite_life_value=-1;//菁英怪血量
	int elite_damage=-1;//菁英怪攻擊
	int elite_range=-1;//菁英怪射程
	
};