#pragma once
#include <fstream>
#include <string>
using namespace std;
class Gloom_Haven;
class Map;
class Character;
#define err "input error,please input again!"
//輸入處理function
int character_amount_input();//角色數量輸入
void character_data_input(Character& life, Character* db, int total_chr,char);//brute 0 1 2 3 4 5
void open_file(fstream&,string);//地圖路徑輸入
string wasd();//移動指令
string character_card_choose();//A 0 3 B -1，bool回傳false代表check或輸入錯誤，重新輸入
string character_card_first_ud();//角色輸入第一張使用的牌與上半部或下半部(2u)

int getline_int();//數字輸入
char getline_char();//字元輸入
bool is_num(string);//該string是否為純數字