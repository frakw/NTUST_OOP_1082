#pragma once
#include <string>
using namespace std;
class Creature;
class Skill;
class Monster : public Creature{
public:
	Monster();
	Monster& operator=(const Monster& input);
	void set_debug();
	void switch_status(int num);
	void choose_card();
	virtual void print() override;//排序後的列印
	virtual void action() override;//行動
	virtual void round_end() override;//該回合結束後的重整(重設數值)
	void to_discard();
	void attack(const Skill const&);//角色與怪物的attck各自分開
	int damage=0;
	int range=0;//0為近戰怪
	bool show = true;//是(true)否(false)出現在場上
	bool show_in_room = false;//是否在房間裡
	//int debug_mode_card_number=0;//debug_mode，紀錄卡片編號，從0開始出
	//elite系列------------------------------------
	bool elite = false; //是(true)否(false)為菁英
	int elite_max_life_value=-1;//菁英怪最大血量
	int elite_damage=-1;//菁英怪攻擊
	int elite_range=-1;//菁英怪射程
	//---------------------------------------------
	bool finished_show = false;
	static std::map<string,int> race_card_number;
};