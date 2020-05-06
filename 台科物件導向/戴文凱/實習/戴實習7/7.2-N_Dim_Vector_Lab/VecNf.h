#pragma once
#include<iostream>
#include<fstream>
using namespace std;
class VecNf {
public:
	VecNf();//Construct a one - dimensional zero vector in default.
	VecNf(float* dest, int cnt);//Construct a cnt dimensional vector using the first cnt  numbers in dest.
	VecNf(const VecNf& rhs);//Construct a new vector from a VecNf.
	~VecNf();
	VecNf operator+(VecNf const&);
	VecNf operator-(VecNf const&);
	float operator*(VecNf const&);
	VecNf& operator=(const VecNf&);
	float& operator[](int);
	VecNf operator*(double);
	friend VecNf operator*(double, VecNf&);
	int Size() {
		return cnt;
	}
private:
	float* element = nullptr;
	int cnt= 1;
};