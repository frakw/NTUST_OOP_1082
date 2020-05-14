#include"Gloom_Haven.h"
#include <iostream>
Gloom_Haven::Gloom_Haven(tuple<Character*, Monster*, Map*> input, bool mode) :DEBUG_MODE(mode) {
	map = get<2>(input);
	map->player = get<0>(input);
	map->enemy = get<1>(input);
}
void Gloom_Haven::seiting(tuple<Character*, Monster*, Map*> input, bool mode) {
	DEBUG_MODE = mode;
	map = get<2>(input);

	map->player = get<0>(input);
	map->enemy = get<1>(input);

	this->player = get<0>(input);
	this->enemy = get<1>(input);
}

void Gloom_Haven::start() {
	
}