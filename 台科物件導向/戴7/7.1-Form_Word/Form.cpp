#include"Form.h"
#include<fstream>

void Form::SetInputWord(string inputWord)
{
	word = inputWord;
}

void Form::ProcessInputWord()
{
	for (int i = 0; i < word.length(); i++)
	{
		if (isupper(word[i]))
		{
			word[i] = tolower(word[i]);
		}
	}
}

void Form::SetFileName(string fileName)
{
	name = fileName;
}

void Form::Load_CompareWord()
{
	ifstream file;
	string input;
	int alpha_count[26] = { 0 };//a~z
	file.open(name, ifstream::in);//ios::in 檔案開啟為讀取(輸入)狀態
	for (int i = 0;i < word.length();i++) {
		alpha_count[word[i] - 'a']++;
	}
	while (file >> input)
	{
		int input_alpha_count[26] = { 0 };
		for (int i = 0;i < input.length();i++) {
			input_alpha_count[tolower(input[i]) - 'a']++;
		}
		int i;
		for (i = 0;i < 26;i++) {
			if (input_alpha_count[i] > alpha_count[i]) {
				break;
			}
		}
		if (i == 26) {//代表a~z都沒超過限制，印出
			output.push_back(input);
		}
	}
	file.close();
}

void Form::PrintFoundWords()
{
	for (int i = 0;i < output.size();i++) {
		cout << output[i] << endl;
	}
}