#pragma once
#include <fstream>
#include <string>
using namespace std;
class Gloom_Haven;
class Map;
class Character;
#define err "input error,please input again!"
int character_amount_input();
void character_data_input(Character& life, Character* db, int total_chr,char);//brute 0 1 2 3 4 5
void open_file(fstream&,string);//map1.txt
string wasd();
string character_card_choose();//A 0 3 B -1，bool回傳false代表check或輸入錯誤，重新輸入
string character_card_first_ud();//角色輸入第一張使用的牌與上半部或下半部(2u)

int getline_int();
char getline_char();
bool is_num(string);