#pragma once
#include<string>
#include<ctype.h>
#include<iostream>
#include<vector>
using namespace std;
class Form
{
private:

public:
	string word,name;
	vector<string> output;
	void SetInputWord(string inputWord);//設定Input
	void ProcessInputWord();//處理 Input 的資訊
	void SetFileName(string fileName);//設定檔案名稱
	void Load_CompareWord();//讀檔並且比較
	void PrintFoundWords();//印出符合的字
};
