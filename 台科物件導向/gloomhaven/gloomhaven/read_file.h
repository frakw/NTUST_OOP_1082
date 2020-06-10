#pragma once

class Skill;
class Character;
class Monster;
class Map;
class Card;
using namespace std;


class TXT {//讀檔處理class
public:
	TXT() {}
	~TXT();
	void input_character_data();
	void read_character(string filename);//動態配置全部卡牌堆，存入database
	void read_monster(string filename);//動態配置全部卡牌堆，存入database
	void read_map(string filename);
	tuple<Character*, int, Monster*, int, Map*> return_tuple();//動態配置記憶體，然後複製database內容後，傳到gloom_haven執行，釋放記憶體交給gloom_haven   (PPT 40頁)
private:
	Character* character_db = nullptr;//database，角色資料庫
	int chr_db_amount = 0;//database total，角色資料庫數量
	Monster* monster_db = nullptr;//database，怪物資料庫
	int mon_db_amount = 0;//database total，怪物資料庫數量

	Character* character_output = nullptr;//依據輸入從資料庫複製角色後輸出到gloomhaven
	int character_amount = 0;//角色輸出到gloomhaven的數量
	Monster* monster_output = nullptr;//依據txt從資料庫複製怪物後輸出到gloomhaven
	int monster_amount = 0;//怪物輸出到gloomhaven的數量
	Map* map = nullptr;

};