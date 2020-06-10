#pragma once
//增加可讀性的代換
enum dir : char {
	up = 'w',
	left = 'a',
	down = 's',
	right = 'd',
	stay = 'e',
};
enum map_obj : char {
	wall = '0',
	m_floor = '1',
	barrier = '2',
	door = '3',
	select_pos = '_',
	star_pos = '*',
};
enum skill_type {
	move = 0,
	attack = 1,
	heal = 2,
	shield = 3,
};
enum Team_num {
	character = 0,
	monster = 1,
};
enum monster_status {
	disappear = 0,
	normal = 1,
	elite = 2,
};