#ifndef DIARY_H
#define DIARY_H

#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
using namespace std;
typedef struct {
	string name;
	string content;
}event;

typedef struct {
	string name;
	vector<event> event_list;
}day_log;
class Diary {
public:
	static void NewDay(string input);
	static void NewEvent(string creature_name, string input);
	static vector<day_log> day;
};
#endif