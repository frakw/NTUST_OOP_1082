#include"Buff.h"

BuffType StrToType(string _str)
{
	if (_str == "power")
		return BuffType::power;
	else if (_str == "defense")
		return BuffType::defense;
	else
		return BuffType::speed;
}

Buff::Buff() : Buff::Buff(BuffType::power, "", 0, 0, 1)
{}

Buff::Buff(string _type, string _name, int _priority, float _add, float _mul)
{
	type = StrToType(_type);
	name = _name;
	priority = _priority;
	addend = _add;
	multiplier = _mul;
}

float Buff::Apply(float _value)
{
	return roundf(_value * multiplier + addend);
}