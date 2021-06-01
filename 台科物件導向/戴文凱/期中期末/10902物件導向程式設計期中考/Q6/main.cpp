#include "Character.h"
#include <iostream>
using namespace std;
int main()
{
	float base_power, base_defense, base_speed;
	cin >> base_power >> base_defense >> base_speed;
	Character myCharater(base_power, base_defense, base_speed);
        string command;
        while (cin >> command)
	{

		
		if (command == "add")
		{
			string type, name;
			int priority;
			float add, mul;

			cin >> type >> name >> priority >> add >> mul;

			Buff newBuff(type, name, priority, add, mul);
			myCharater.AddBuff(newBuff);
		}
		else if(command == "remove")
		{
			string name;
			cin >> name;
			myCharater.RemoveBuff(name);
		}
		else
		{
			myCharater.Parse();
		}
	}
}
