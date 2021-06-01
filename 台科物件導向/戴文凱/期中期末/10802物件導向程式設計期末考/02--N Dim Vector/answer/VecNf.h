#pragma once
#include <iostream>
#include<stdlib.h>
#include<stdio.h>

using namespace std;

class VecNf {
public:
	int cnt;
	float* dest;

	int Size() {
		return cnt;
	}

	VecNf() {
		cnt = 1;
		dest = new float[1];
		dest[0] = 0;
	}

	VecNf(float* _dest, int _cnt) {
		cnt = _cnt;
		dest = _dest;
	}

	VecNf(const VecNf& rhs) {
		cnt = rhs.cnt;
		dest = new float[cnt];
		for (int i = 0; i < cnt; i++) {
			dest[i] = rhs.dest[i];
		}
	}



	void operator=(const VecNf& other) {
		cout << "ASSIGNMENT!!!" << endl;
		cnt = other.cnt;
		dest = new float[cnt];
		for (int i = 0; i < cnt; i++) {
			dest[i] = other.dest[i];
		}
	}

	float operator[](int index) {
		if (index >= cnt) {
			cout << "Out of range" << endl;
			return 0.0f;
		}

		return dest[index];
	}

	VecNf operator+(VecNf& other) {

		if (other.cnt != cnt) {
			cout << "Dimensions inconsistent" << endl;
			return VecNf();
		}

		float* d = new float[cnt];

		cout << "ADDITION!!!" << endl;
		for (int i = 0; i < cnt; i++) {
			d[i] = dest[i] + other.dest[i];
		}

		return VecNf(d, cnt);
	}

	VecNf operator-(VecNf& other) {

		if (other.cnt != cnt) {
			cout << "Dimensions inconsistent" << endl;
			return VecNf();
		}

		float* d = new float[cnt];

		cout << "SUBTRACTION!!!" << endl;
		for (int i = 0; i < cnt; i++) {
			d[i] = dest[i] - other.dest[i];
		}

		return VecNf(d, cnt);
	}

	float operator*(VecNf& other) {

		if (other.cnt != cnt) {
			cout << "Dimensions inconsistent" << endl;
			return 0.0f;
		}

		cout << "INNER PRODUCT!!!" << endl;

		float sum = 0.0f;
		for (int i = 0; i < cnt; i++) {
			sum += dest[i] * other.dest[i];
		}

		return sum;
	}

	VecNf operator*(float other) {
		float* d = new float[cnt];

		cout << "SCALAR!!!" << endl;
		for (int i = 0; i < cnt; i++) {
			d[i] = dest[i] * other;
		}

		return VecNf(d, cnt);
	}

	VecNf operator*(int other) {
		float* d = new float[cnt];

		cout << "SCALAR!!!" << endl;
		for (int i = 0; i < cnt; i++) {
			d[i] = dest[i] * other;
		}

		return VecNf(d, cnt);
	}

	friend VecNf operator*(int other, const VecNf& dt) {
		float* d = new float[dt.cnt];

		cout << "SCALAR!!!" << endl;
		for (int i = 0; i < dt.cnt; i++) {
			d[i] = dt.dest[i] * other;
		}

		return VecNf(d, dt.cnt);
	}

	friend VecNf operator*(float other, const VecNf& dt) {
		float* d = new float[dt.cnt];

		cout << "SCALAR!!!" << endl;
		for (int i = 0; i < dt.cnt; i++) {
			d[i] = dt.dest[i] * other;
		}

		return VecNf(d, dt.cnt);
	}


	friend ostream& operator<<(ostream& os, const VecNf& dt) {
		os << "(";

		for (int i = 0; i < dt.cnt - 1; i++) {
			os << dt.dest[i] << ",";
		}

		os << dt.dest[dt.cnt - 1];

		os << ")";

		return os;
	}
};