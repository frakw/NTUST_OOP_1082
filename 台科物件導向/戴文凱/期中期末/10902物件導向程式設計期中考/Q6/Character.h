#pragma once
#include <vector>
#include <iostream>
#include "Buff.h"

class Character
{
public:
	Character();
	Character(float _power, float _defense, float _speed);
	~Character();
	void Parse();
	void AddBuff(Buff _buff);
	void RemoveBuff(string _name);

private:
	float BasePower;
	float BaseDefense;
	float BaseSpeed;
	vector<Buff> buffList;

	float BuffPower;
	float BuffDefense;
	float BuffSpeed;
	void ParseBuffList();
	void RecalculateBuff();
};