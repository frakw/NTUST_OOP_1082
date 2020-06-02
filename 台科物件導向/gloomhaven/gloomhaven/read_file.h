#pragma once

class Skill;
class Character;
class Monster;
class Map;
class Card;
using namespace std;


class TXT {
public:
	TXT() {}
	~TXT();
	void input_character_data();
	void read_character(string filename);//動態配置全部卡牌堆，存入database
	void read_monster(string filename);//動態配置全部卡牌堆，存入database
	void read_map(string filename);
	tuple<Character*, int, Monster*, int, Map*> return_tuple();//動態配置記憶體，然後複製database內容後，傳到gloom_haven執行，釋放記憶體交給gloom_haven   (PPT 40頁)
private:
	Character* character_db = nullptr;//database
	int chr_db_amount = 0;//database total
	Monster* monster_db = nullptr;//database
	int mon_db_amount = 0;//database total

	Character* character_output = nullptr;//character output
	int character_amount = 0;
	Monster* monster_output = nullptr;//monster output
	int monster_amount = 0;
	Map* map = nullptr;

};