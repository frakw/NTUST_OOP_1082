#include <iostream>
#include <windows.h>
#include <conio.h>
#include <thread>
#include <ctype.h>
#include <random>
#include <string>
#define to_sec(x) ((double)(x) / (double)CLOCKS_PER_SEC)
using std::endl;
void gotoxy(int, int);
void SetColor(int);
void setcolor_with_two_coor(COORD, COORD, int );
void check_click_stop();
void check_click_stop1();
void check_click_stop2();
void check_click_stop3();
void set_big_word_color(char,int);
void big_word_init();
int win_cwidth;
int win_cheight;
clock_t click_time=0;
clock_t click_time1 = 0;
clock_t click_time2 = 0;
clock_t click_time3 = 0;
bool w_color_on = false;
bool a_color_on = false;
bool s_color_on = false;
bool d_color_on = false;
HANDLE hin = GetStdHandle(STD_OUTPUT_HANDLE);
const char* wasd[4][8] = {
{
" _             _ ",
"(_)           (_)",
"(_)           (_)",
"(_)     _     (_)",
"(_)   _(_)_   (_)",
"(_)  (_) (_)  (_)",
"(_)_(_)   (_)_(_)",
"  (_)       (_)  "
}, {
"       _       ",
"     _(_)_     ",
"   _(_) (_)_   ",
" _(_)     (_)_ ",
"(_) _  _  _ (_)",
"(_)(_)(_)(_)(_)",
"(_)         (_)",
"(_)         (_)"
}, {
"   _  _  _  _   ",
" _(_)(_)(_)(_)_ ",
"(_)          (_)",
"(_)_  _  _  _   ",
"  (_)(_)(_)(_)_ ",
" _           (_)",
"(_)_  _  _  _(_)",
"  (_)(_)(_)(_)  "
}, {
" _  _  _  _    ",
"(_)(_)(_)(_)   ",
"(_)       (_)  ",
"(_)        (_) ",
"(_)         (_)",
"(_)        (_) ",
"(_) _  _  (_)  ",
"(_)(_)(_)(_)   "
}
};
int main() {
	unsigned int color = FOREGROUND_RED | FOREGROUND_GREEN
		| BACKGROUND_BLUE;
	// 前景為黃色 背景為藍色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
	printf("Hello the world!!\n");
	color = FOREGROUND_GREEN | FOREGROUND_INTENSITY
		| BACKGROUND_RED;
	// 前景為亮綠色 背景為紅色
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);


	printf("Hello the world!!\n");
	//Sleep(3000);
	unsigned int win_width = GetSystemMetrics(SM_CXSCREEN);
	unsigned int win_height = GetSystemMetrics(SM_CYSCREEN);

	//SetWindowLong(GetForegroundWindow(), GWL_STYLE, (GetWindowLong(GetForegroundWindow(), GWL_STYLE) | WS_POPUP | WS_MAXIMIZE) & ~WS_CAPTION & ~WS_THICKFRAME & ~WS_BORDER);
	//SetWindowPos(GetForegroundWindow(), HWND_TOP, 0, 0, win_width, win_height, 0);


	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);

	win_cwidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;
	win_cheight = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;



	COORD NewSBSize;

	NewSBSize.X = csbi.dwSize.X - 2;


	NewSBSize.Y = csbi.dwSize.Y;

	SetConsoleScreenBufferSize(hin, NewSBSize);
	/*=========================================random===========================================================*/
	std::random_device rd;
	std::default_random_engine gen = std::default_random_engine(rd());
	std::uniform_int_distribution<int> dis(1, 10);
	/*==============================================================================================================*/


	DWORD WriteWord;
	COORD pos;
	//const char* wasd[9] ={
	//" _             _        _          _  _  _  _    _  _  _  _    ",
	//"(_)           (_)     _(_)_      _(_)(_)(_)(_)_ (_)(_)(_)(_)   ",
	//"(_)           (_)   _(_) (_)_   (_)          (_)(_)       (_)  ",
	//"(_)     _     (_) _(_)     (_)_ (_)_  _  _  _   (_)        (_) ",
	//"(_)   _(_)_   (_)(_) _  _  _ (_)  (_)(_)(_)(_)_ (_)         (_)",
	//"(_)  (_) (_)  (_)(_)(_)(_)(_)(_) _           (_)(_)        (_) ",
	//"(_)_(_)   (_)_(_)(_)         (_)(_)_  _  _  _(_)(_) _  _  (_)  ",
	//"  (_)       (_)  (_)         (_)  (_)(_)(_)(_)  (_)(_)(_)(_)   "
	//};
	pos.X = win_cwidth/2 -32, pos.Y = win_cheight - 8; 
	big_word_init();
/*
      ██
████████ ███████ ████████ ███████
 _             _        _          _  _  _  _   _  _  _  _    
(_)           (_)     _(_)_      _(_)(_)(_)(_)_(_)(_)(_)(_)   
(_)           (_)   _(_) (_)_   (_)          (_)(_)      (_)_ 
(_)     _     (_) _(_)     (_)_ (_)_  _  _  _   (_)        (_)
(_)   _(_)_   (_)(_) _  _  _ (_)  (_)(_)(_)(_)_ (_)        (_)
(_)  (_) (_)  (_)(_)(_)(_)(_)(_) _           (_)(_)       _(_)
(_)_(_)   (_)_(_)(_)         (_)(_)_  _  _  _(_)(_)_  _  (_)  
  (_)       (_)  (_)         (_)  (_)(_)(_)(_) (_)(_)(_)(_)   
*/


	//std::cout << "█  █  █"<<endl;
	//std::cout << "  ███  █" << endl;
	std::thread wthread(check_click_stop);
	std::thread athread(check_click_stop1);
	std::thread sthread(check_click_stop2);
	std::thread dthread(check_click_stop3);
	pos.Y = 0;
	char pre = 0;
	while (char temp = _getch()) {
			switch (temp)
			{
			case'W':case'w': if (!w_color_on) { set_big_word_color(temp, 64);  w_color_on = true;} click_time = clock(); break;
			case'A':case'a': if (!a_color_on) { set_big_word_color(temp, 128); a_color_on = true;}click_time1 = clock(); break;
			case'S':case's': if (!s_color_on) { set_big_word_color(temp, 192); s_color_on = true;}click_time2 = clock(); break;
			case'D':case'd': if (!d_color_on) { set_big_word_color(temp, 223); d_color_on = true;}click_time3 = clock(); break;
			case 27://ESC鍵
				system("pause");
				return 0;
			}
			Sleep(15);
	}
	wthread.join();
	system("pause");
	return 0;
}

void check_click_stop() {
	while (1) {
		if (w_color_on && to_sec(clock() - click_time) >= 0.5) {
			set_big_word_color('w', 7);
			w_color_on = false;
		}
		Sleep(50);//讓CPU使用率降低
	}
}
void check_click_stop1() {
	while (1) {
		if (a_color_on && to_sec(clock() - click_time1) >= 0.5) {
			set_big_word_color('a', 7);
			a_color_on = false;

		}
		Sleep(50);

	}
}
void check_click_stop2() {
	while (1) {
		if (s_color_on && to_sec(clock() - click_time2) >= 0.5) {
			set_big_word_color('s', 7);
			s_color_on = false;
		}
		Sleep(50);

	}
}
void check_click_stop3() {
	while (1) {
		if (d_color_on && to_sec(clock() - click_time3) >= 0.5) {
			set_big_word_color('d', 7);
			d_color_on = false;
		}
		Sleep(50);

	}
}

void gotoxy(int xpos, int ypos)
{
	COORD scrn;
	HANDLE hOuput = GetStdHandle(STD_OUTPUT_HANDLE);
	scrn.X = xpos; scrn.Y = ypos;
	SetConsoleCursorPosition(hOuput, scrn);
}

void SetColor(int color = 7)
{
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
}

void set_big_word_color(char wasd_char,int color) {
	int x= win_cwidth / 2 - 32,j;
	switch (wasd_char) {
	case 'w':case'W':  j = 0; break;
	case 'a':case'A': x += 17; j = 1; break;
	case 's':case'S': x += 32; j = 2; break;
	case 'd':case'D': x += 48; j = 3; break;
	}
	for (int i = 0;i < 8;i++) {
		gotoxy(x, win_cheight - 7 + i);
		SetConsoleTextAttribute(hin, color);
		std::cout << wasd[j][i];
	}
}

void big_word_init() {
	SetConsoleTextAttribute(hin, 7);
	for (int i = 0;i < 8;i++) {
		gotoxy(win_cwidth / 2 - 32, win_cheight - 7 + i);
		for (int j = 0;j < 4;j++) {
			std::cout << wasd[j][i];
		}
		std::cout << endl;
	}
	//SetConsoleTextAttribute(hin, 7);
}
