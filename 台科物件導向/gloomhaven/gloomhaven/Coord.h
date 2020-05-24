#pragma once
typedef struct {
	int x, y;
}Coord;
#define coord_in(src,coord) ((src)[(coord).y][(coord).x])