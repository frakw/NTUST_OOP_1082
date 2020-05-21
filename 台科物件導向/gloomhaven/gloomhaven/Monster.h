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
	void choose_card(bool);//bool為debug mode
	void print()override;//排序後的列印
	void action()override;//行動
	void attack();//角色與怪物的attck各自分開
	int damage=0;
	int range=0;//0為近戰怪
	bool show = true;//是(true)否(false)出現在場上
	bool show_in_room = false;//是否在房間裡
	//Card use_card;//該回合使用的卡，已轉移至basic
	int debug_mode_card_number=0;//debug_mode，紀錄卡片編號，從0開始出
	//elite系列------------------------------------
	bool elite = false; //是(true)否(false)為菁英
	int elite_max_life_value=-1;//菁英怪最大血量
	int elite_damage=-1;//菁英怪攻擊
	int elite_range=-1;//菁英怪射程
	//---------------------------------------------
	
};