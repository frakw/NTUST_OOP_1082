#include"VecNf.h"
VecNf::VecNf() {//Construct a one - dimensional zero vector in default.
	
	this->~VecNf();
	cnt = 1;
	element = new float[1];
	element[0] = 0.0f;
}
VecNf::VecNf(float* dest, int cnt_in) {//Construct a cnt dimensional vector using the first cnt  numbers in dest.
	
	this->~VecNf();
	cnt = cnt_in;
	element = new float[cnt];
	for (int i = 0;i < cnt;i++) {
		element[i] = dest[i];
	}
}
VecNf::VecNf(const VecNf& rhs) {//Construct a new vector from a VecNf.
	if (this == &rhs) {
		return;
	}
	this->~VecNf();
	cnt = rhs.cnt;
	element = new float[cnt];
	for (int i = 0;i < cnt;i++) {
		element[i] = rhs.element[i];
	}
}

VecNf::~VecNf() {
	delete[] element;
	element = nullptr;
}
VecNf VecNf::operator+(VecNf const& in) {
	
	VecNf result;
	if (cnt != in.cnt) {
		cout << "dimensions inconsistent" << endl;
		return result;
	}
	result.cnt = cnt;
	result.element = new float[result.cnt];
	for (int i = 0;i < cnt;i++) {
		result.element[i] = element[i] + in.element[i];
	}
	return result;
}
VecNf VecNf::operator-(VecNf const& in) {
	VecNf result;
	if (cnt != in.cnt) {
		cout << "dimensions inconsistent" << endl;
		return result;
	}
	result.cnt = cnt;
	result.element = new float[result.cnt];
	for (int i = 0;i < cnt;i++) {
		result.element[i] = element[i] - in.element[i];
	}
	return result;
}
float VecNf::operator*(VecNf const& in) {
	float sum = 0;
	if (cnt != in.cnt) {
		cout << "dimensions inconsistent" << endl;
		return 0.0f;
	}
	for (int i = 0;i < cnt;i++) {
		sum += element[i] * in.element[i];
	}
	return sum;
}
VecNf& VecNf::operator=(const VecNf& in) {
	cout << "ASSIGNMENT!!!" << endl;
	if (this == &in) {
		return *this;
	}
	this->~VecNf();
	cnt = in.cnt;
	element = new float[cnt] {};//{}初始化全部為0
	for (int i = 0;i < cnt;i++) {
		element[i] = in.element[i];
	}
	return *this;
}

float& VecNf::operator[](int index) {
	return element[index];
}

VecNf VecNf::operator*(double a) {
	VecNf result;
	result.cnt = cnt;
	result.element = new float[result.cnt];
	for (int i = 0;i < result.cnt;i++) {
		result.element[i] = a * element[i];
	}
	return result;
}
VecNf operator*(double a, VecNf& x) {
	VecNf result;
	result.cnt = x.cnt;
	result.element = new float[result.cnt];
	for (int i = 0;i < result.cnt;i++) {
		result.element[i] = a * x.element[i];
	}
	return result;
}