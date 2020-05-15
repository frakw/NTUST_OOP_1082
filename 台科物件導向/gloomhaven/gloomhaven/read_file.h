#pragma once
#include <string>
#include <iostream>
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include <vector>
#include <string>
#include "basic.h"
using namespace std;


class TXT {
public:
	TXT() {}
	TXT(string in_filename) :filename(in_filename){}
	~TXT() {//銷毀資料庫
		if (character != nullptr) {
			delete[] character;
		}
		if (monster != nullptr) {
			delete[] monster;
		}
	}
	void set_filename(string in) {
		filename = in;
	}
	void read_character();//動態配置全部卡牌堆，存入database
	bool check_character();
	void read_monster();//動態配置全部卡牌堆，存入database
	bool check_monster();
	Map* read_map();
	bool check_map();
	tuple<Character*, Monster*, Map*> return_tuple();//動態配置記憶體，然後複製database內容後，傳到gloom_haven執行，釋放記憶體交給gloom_haven   (PPT 40頁)
private:
	Character* character = nullptr;//database
	int total_chr;
	Monster* monster = nullptr;//database
	Monster* monput = nullptr;//monster output
	int total_mon;
	string filename;
	int database_total=0;
};