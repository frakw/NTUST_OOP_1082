#include "basic.h"
#include "read_file.h"
#include "Character.h"
#include "Monster.h"
#include "map.h"
#include <tuple>
#include <utility>
#include <iostream>
#include"Gloom_Haven.h"
using namespace std;
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

void Gloom_Haven::stop() {
	
}

Gloom_Haven::Gloom_Haven() {}
Gloom_Haven::Gloom_Haven(bool mode) :DEBUG_MODE(mode) {

}
Gloom_Haven::Gloom_Haven(tuple<Character*, Monster*, Map*> input, bool mode) {
	
}
Gloom_Haven::~Gloom_Haven() {
}