#pragma once
#include<string>
#include<cmath>
using namespace std;

enum class BuffType {power, defense, speed};

class Buff
{
public:
	BuffType type;
	string name;
	int priority;

	Buff();
	Buff(string _type, string _name, int _priority, float _add, float _mul);

	float Apply(float _value);

private:
	float addend;
	float multiplier;
};