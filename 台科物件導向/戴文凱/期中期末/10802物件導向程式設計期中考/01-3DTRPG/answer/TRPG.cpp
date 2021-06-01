#include <iostream>
using namespace std;

constexpr inline int max(int a, int b) {
	return a > b ? a : b;
}

class Entity
{
private:
	int hp;
	int atk;
	int def;
public:
	Entity(int hp, int atk, int def) : hp(hp), atk(atk), def(def) {};
	bool Attack(const Entity& enemy) {
		for (int b_hp = enemy.hp; hp > 0 || b_hp > 0;) {
			b_hp -= max(0, atk - enemy.def);
			cout << "Player:" << hp << " Enemy:" << b_hp << endl;
			if (b_hp <= 0) {
				return true;
			}
			hp -= max(0, enemy.atk - def);
			cout << "Player:" << hp << " Enemy:" << b_hp << endl;
			if (hp <= 0) {
				return false;
			}
		}
	}
};

int main()
{
	int a, b, c;
	cin >> a >> b >> c;
	Entity player(a, b, c);
	while (cin >> a >> b >> c) {
		Entity monster(a, b, c);
		if (player.Attack(monster)) {
			cout << "Player Win" << endl;
		}
		else {
			cout << "Player Dead" << endl;
			return 1;
		}
	}
}
