#pragma once
typedef struct _Coord_{
	int x, y;
	bool operator==(const struct _Coord_ a) {
		return (a.x == this->x) && (a.y == this->y);
	}
	void to_null() {
		this->x = -1;
		this->y = -1;
	}
	bool is_null() {
		Coord NullCoord = { -1,-1 };
		return NullCoord == *this;
	}
}Coord;
#define coord_in(src,coord) ((src)[(coord).y][(coord).x])
