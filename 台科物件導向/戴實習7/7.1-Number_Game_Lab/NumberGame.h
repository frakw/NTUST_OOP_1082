#pragma once
#include<string>
#include<vector>
#include<iostream>
#include<fstream>
#include<cmath>
#include<bitset>
using namespace std;
class  NumberGame {
public:
	void SetInput(int);//set the given integer A.
	void ProcessInput();//splitting the integer A into several digits.
	void SetFileName(string);// set the file name of the file where list S is located.
	void LoadNumberList();//read list S from the file.
	void PrintAllValid();//print all the valid numbers in S ascendingly
	void Reset(); //reset all variables.
	int input;
	string filename;
	vector<int> valid;
	vector<int> result;
};