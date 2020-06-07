#pragma once
using namespace std;
class Creature;
class Monster;
class Map;


class Skill {
public:
	Skill();
	Skill(string name, int val);
	Skill(int in_type, int val);
	Skill(const Skill&);
	Skill& operator=(const Skill&);
	void set(string name, int val);
	int type=-1;//0 move 1 attack 2 heal 3 shield
	int value=-1;//技能數值
	int range = 0;//attack時才用到，range 0 1效果皆相同，但0是指定為近戰怪，印print時會不同，角色range預設為1(角色屬於遠程)
	string move_step="";//只在怪物卡技能為move時使用，存wasd
};

class Card {
public:
	Card();
	Card(const Card& input);//copy constructor，因為skill會當成參數傳到funtion裡
	Card(int in_agility, bool mark, Skill* a);
	Card(int in_agility, bool mark, Skill* a, Skill* b);
	~Card();
	Card& operator=(const Card& input);

	bool available=true;//此卡是否還可被使用(移除)
	bool discard = false;//是(true)否(false)在棄牌堆

	Skill* skill_up = nullptr;//卡牌上半部技能陣列頭指標，怪物卡的資訊都存在這
	int skill_up_amount = 0;//卡牌上半部技能數

	Skill* skill_down = nullptr;//卡牌下半部技能陣列頭指標，怪物卡沒下半部，nullptr
	int skill_down_amount = 0;//卡牌下半部技能數

	int number=0;//編號
	int agility=0;//敏捷值
	bool rewash_mark = false;//重洗標記，角色沒有重洗標記(false)
};


class Creature {
public:
	Creature();
	~Creature();
	Card* card = nullptr;//選擇卡牌
	string name="";
	Card& find_card(int);//int 傳入編號number，回傳該Card reference
	void move(string,int);//int為最大步數，error move後檢查，只適用於角色(怪物move的int可隨便輸入)
	void heal(int);//增加血量(不超過最大)，不要在action以外的地方呼叫
	void shield(int);//增加護甲值，不要在action以外的地方呼叫，int為攻擊值
	void be_attack(char,int);//被攻擊時呼叫，char為攻擊者代號，輸出護甲與剩餘血量
	void discard_to_hand();//棄牌堆所有牌移回手牌，但不包含已被移除的牌(availible == false)
	void check_card();//印出卡牌編號(手牌與棄牌)，編號由小到大
	int card_available_amount();//持有卡牌數(棄牌堆+手牌)
	int card_hand_amount();//可用卡牌數
	int card_discard_amount();//棄牌堆數
	bool card_in_hand(int);//傳入編號，回傳該牌是不是手牌，error handling用
	bool card_in_discard(int);//傳入編號，回傳該牌在不在棄牌堆，error handling用
	virtual void print()/*排序後的列印*/ { cout << "virtual error" << endl; }
	virtual void action(bool) /*行動，bool為debug_mode*/{ cout << "virtual error" << endl; }
	virtual void round_end(bool) /*回合結算階段，該回合結束後的重整(重設數值)*/{ cout << "virtual error" << endl; }
	void check();//角色行動前，輸入check，要列出所有角色與怪物的hp與防禦值
	Card use_card[2];//若為怪物則只有一張卡，存在use_card[0]
	int life_value=0;//目前血量
	int max_life_value = 0;//最大血量
	int card_amount=0;//可選卡牌數量
	int card_total =0;//該總卡牌數量(資料庫時使用)，遊玩時不影響
	char code=0;//代號
	int TmpShield = 0;//該輪護甲值
	Coord position = {-1,-1};
	int team_num = 0;//隊伍編號，角色為0，怪物為1
	Map* map = nullptr;
	bool finished_choose = false;//該回合是否完成選牌或選擇長休
};


