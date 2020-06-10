#pragma once
using namespace std;
class Creature;
class Map;
class Skill;
class Character : public Creature {
public:
	Character();
	virtual ~Character();
	Character& operator=(const Character& input);
	void choose_card(string);//選擇2張卡或長休或check，bool回傳是否選擇成功，string傳入"0 3"
	virtual void print() override;//排序後的列印
	virtual void action() override;//行動
	virtual void round_end() override;//該回合結束後的重整(重設數值)
	void run_skill(const Skill const&);//執行技能
	void attack(const Skill const&);//角色與怪物的attck各自分開
	bool sleep = false;//是否長休	
};