#ifndef Point_H
#define Point_H
class Point {
public:
	void Set(int, int);
	void Move(int, int);
	int RetrieveVertical();
	int RetrieveHorizontal();
	void Rotate();
private:
	int x;
	int y;
};
#endif //Point_H