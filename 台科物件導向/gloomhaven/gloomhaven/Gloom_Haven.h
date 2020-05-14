#pragma once
//total: 8 * .h file
#include "Character.h"
#include "Monster.h"
#include "Map.h"
#include "Data.h"
#include "Skill.h"
#include "Action.h"
#include "Card.h"

class Gloom_Haven {
public:
	Gloom_Haven();
	void set_mode(bool);
	void start();
private:
	bool DEBUG_MODE = false;
};