#include "Point.h"
#include <iostream>
#include <algorithm> 
void Point::Set(int a, int b) {
	x = a;
	y = b;
}
void Point::Move(int a, int b) {
	x += a;
	y += b;
}
int Point::RetrieveVertical() {
	return x;
}
int Point::RetrieveHorizontal() {
	return y;
}
void Point::Rotate() {
	std::swap(x, y);
	y *= -1;
}
