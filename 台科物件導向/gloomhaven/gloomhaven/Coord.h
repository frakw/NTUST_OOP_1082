#pragma once
//增加可讀性的巨集
#define UP(coord) Coord((coord).x,(coord).y-1)
#define DOWN(coord) Coord((coord).x,(coord).y+1)
#define LEFT(coord) Coord((coord).x-1,(coord).y)
#define RIGHT(coord) Coord((coord).x+1,(coord).y)
typedef struct _Coord_ Coord;
struct _Coord_ {//coord的null代表(-1,-1)
	_Coord_() :x(0), y(0) {}
	_Coord_(int ix, int iy) :x(ix), y(iy) {}
	int x, y;
	bool operator==(const Coord const& a) {
		return (a.x == this->x) && (a.y == this->y);
	}
	bool operator!=(const Coord const& a) {
		return !(*this==a);
	}
	void to_null() {
		this->x = -1;
		this->y = -1;
	}
	bool is_null() {
		Coord NullCoord = { -1,-1 };
		return NullCoord == *this;
	}
	bool not_null() {
		return !is_null();
	}
	Coord up() {
		return UP(*this);
	}
	Coord down() {
		return DOWN(*this);
	}
	Coord left() {
		return LEFT(*this);
	}
	Coord right() {
		return RIGHT(*this);
	}
};
#define coord_in(src,coord) ((src)[(coord).y][(coord).x])
