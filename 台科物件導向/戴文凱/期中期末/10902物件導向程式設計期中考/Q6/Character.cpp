#include "Character.h"

Character::Character() : Character::Character(10, 10, 10)
{}

Character::Character(float _power, float _defense, float _speed)
{
	BasePower = _power;
	BaseDefense = _defense;
	BaseSpeed = _speed;
	buffList.clear();

	RecalculateBuff();
}

Character::~Character()
{
	buffList.clear();
}

void Character::Parse()
{
	cout << "Power: " << BuffPower << endl;
	cout << "Defense: " << BuffDefense << endl;
	cout << "Speed: " << BuffSpeed << endl;
	ParseBuffList();
}

void Character::AddBuff(Buff _buff)
{
	// checks if name duplicated, discard the buff.
	for (int i = 0; i < buffList.size(); i++)
	{
		if (buffList[i].name == _buff.name)
		{
			cout << "Add BUFF Failed!" << endl;
			return;
		}
	}

	// insert to the proper ordered index. 
	bool hasInserted = false;
	for (vector<Buff>::iterator iter = buffList.begin(); iter != buffList.end(); iter++)
	{
		if (iter->priority < _buff.priority
			|| (iter->priority == _buff.priority && iter->type > _buff.type))
		{
			buffList.insert(iter, _buff);
			hasInserted = true;
			break;
		}
	}
	if (!hasInserted)
	{
		buffList.push_back(_buff);
	}

	// re-apply all buff
	RecalculateBuff();
}

void Character::RemoveBuff(string _name)
{
	// search by name. If found, remove the buff and return function.
	for (vector<Buff>::iterator iter = buffList.begin(); iter != buffList.end(); iter++)
	{
		if (iter->name == _name)
		{
			buffList.erase(iter);
			RecalculateBuff();
			return;
		}
	}

	// if no found, prints messege;
	cout << "Remove BUFF Failed!" << endl;
}

void Character::ParseBuffList()
{
	cout << "Buff List: ";
	if (buffList.empty())
	{
		cout << "No Buff" << endl;
		return;
	}
	for (int i = 0; i < buffList.size(); i++)
	{
		cout << buffList[i].name;
		if (i != buffList.size() - 1)
			cout << ", ";
	}
	cout << endl;
}

void Character::RecalculateBuff()
{
	BuffPower = BasePower;
	BuffDefense = BaseDefense;
	BuffSpeed = BaseSpeed;

	for (int i = 0; i < buffList.size(); i++)
	{
		// use type to separate the attributes
		switch (buffList[i].type)
		{
		case BuffType::power:
			BuffPower = buffList[i].Apply(BuffPower);
			break;
		case BuffType::defense:
			BuffDefense = buffList[i].Apply(BuffDefense);
			break;
		case BuffType::speed:
			BuffSpeed = buffList[i].Apply(BuffSpeed);
			break;
		default:
			break;
		}
	}
}