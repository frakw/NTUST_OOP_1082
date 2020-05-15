#pragma once
class Character;//不可include 標頭檔，會出現遺漏類型規範-假設為int
class Monster;//不可include 標頭檔，會出現遺漏類型規範-假設為int
using namespace std;

class Map {
public:
	Map();
	Map(int in_row, int in_col);
	~Map();
	void set(string input);
	void choose_pos(int,string);//int為第幾隻腳色，string 為wasd
	void change_char();//變更選擇位置的char與怪物位置的char
	void check_room();//檢查可視範圍，可視座標show[y][x]設為true
	void fill_room(Coord pos);//遞迴函式，由check_room呼叫
	void show_room();//呼叫前記得先check找出可視範圍
	void update_all_creature();//更新生物位置，或死亡刪除
	Coord& find_pos(Coord*, int max, Coord pos);
	int row=0, col=0;
	char** body = nullptr;
	bool** show = nullptr;
	Coord star_pos;//星星位置
	Coord start_pos[4] = {};//可選位置，設為-1,-1代表已選擇
	Coord fill_start;//遞迴起始位置，預設start_pos[0]
	Character* character = nullptr;
	int character_amount = 0;
	Monster* monster = nullptr;
	int monster_amount = 0;
};