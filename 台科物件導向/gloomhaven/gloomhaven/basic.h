#pragma once
using namespace std;
class Creature;
class Monster;
class Skill {
public:
	Skill();
	Skill(string name, int val);
	Skill(int in_type, int val);
	void set(string name, int val);
	int type=-1;
	int value=-1;
	int range = -1;//attack時才用到
	string move_step;//只在怪物卡技能為move時使用，存wasd
};

class Card {//copy constructor
public:
	Card();
	Card(const Card& input);
	Card(int in_agility, bool mark, Skill* a);
	Card(int in_agility, bool mark, Skill* a, Skill* b);
	~Card();
	Card& operator=(const Card& input);
	bool available=true;//此卡是否還可被使用
	bool discard = false;//是(true)否(false)在棄牌堆
	Skill* skill_up = nullptr;
	int skill_up_amount = 0;
	Skill* skill_down = nullptr;//怪物卡沒下半部，nullptr
	int skill_down_amount = 0;
	int number=0;//編號
	int agility=0;//敏捷值
	bool rewash_mark = false;//重洗標記，角色沒有重洗標記(false)
};


class Creature {
public:
	Creature();
	Creature(string in_name, int val, int in_card_amount);
	~Creature();//暫時不用virtual
	Card* card = nullptr;//選擇卡牌
	string name="";
	Card& find_card(int);//int 傳入編號number，回傳該Card reference
	//virtual void move() = 0;
	//virtual void attack() = 0;
	void heal(int);//增加血量(不超過最大)
	void discard_to_hand();//棄牌堆所有牌移回手牌，但不包含已被移除的牌(availible == false)
	void check_card();//印出卡牌編號(手牌與棄牌)，編號由小到大
	int card_available_amount();//持有卡牌數(棄牌堆+手牌)
	int card_hand_amount();//可用卡牌數
	int card_throw_amount();//棄牌堆數
	virtual void print() {}//排序後的列印
	virtual void action() {}//行動
	Card use_card[2];//若為怪物則只有一張卡
	int life_value=0;//目前血量
	int max_life_value = 0;//最大血量
	int card_amount=0;//可選卡牌數量
	int card_total =0;//總卡牌數量
	char code=0;//代號
	//int TmpAgility=0;//該輪敏捷值，已被上方的選擇卡牌取代
	//int TmpShield = 0;//該輪護甲值
	Coord position = {-1,-1};
	int team_num = 0;//隊伍編號，角色為0，怪物為1

};


