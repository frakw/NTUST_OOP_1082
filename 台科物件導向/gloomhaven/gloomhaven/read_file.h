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
	~TXT() {//銷毀資料庫
		if (character != nullptr) {
			delete[] character;
			character = nullptr;
		}
		if (monster != nullptr) {
			delete[] monster;
			monster = nullptr;
		}
		if (map != nullptr) {
			delete map;
			map = nullptr;
		}
	}
	void input_character_data();
	void read_character(string filename);//動態配置全部卡牌堆，存入database
	bool check_character_txt();
	void read_monster(string filename);//動態配置全部卡牌堆，存入database
	bool check_monster_txt();
	void read_map(string filename);
	bool check_map();
	tuple<Character*, int, Monster*, int, Map*> return_tuple();//動態配置記憶體，然後複製database內容後，傳到gloom_haven執行，釋放記憶體交給gloom_haven   (PPT 40頁)
private:
	Character* character = nullptr;//database
	int total_chr=0;
	Monster* monster = nullptr;//database
	int total_mon = 0;


	Character* chrput = nullptr;//character output
	int Character_amount = 0;
	Monster* monput = nullptr;//monster output
	int Monster_amount = 0;
	Map* map = nullptr;

	int database_total=0;
};