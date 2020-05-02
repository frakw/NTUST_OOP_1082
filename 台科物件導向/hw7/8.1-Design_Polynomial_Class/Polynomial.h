#pragma once
class Polynomial {
private:
	double* coefficient= nullptr;
	int size=0;
public:
	Polynomial();
	~Polynomial();
	Polynomial(const Polynomial&);//copy
	Polynomial(double*, int);
	const Polynomial operator+(const Polynomial&);
	const Polynomial operator-(const Polynomial&);
	const Polynomial operator*(const Polynomial&);
	Polynomial& operator=(const Polynomial&);
	double& operator[](int);
	friend double evaluate(const Polynomial&,const double&);
	int mySize() {
		return size;
	}

	const Polynomial operator+(const double&);
	const Polynomial operator-(const double&);
	const Polynomial operator*(const double&);

	friend const Polynomial operator+(const double&, const Polynomial&);
	friend const Polynomial operator-(const double&, const Polynomial&);
	friend const Polynomial operator*(const double&, const Polynomial&);
	void clear_zero() {
		for (int i = size - 1;!coefficient[i];i--,size--);//從最高次項開始檢查，若為0 size-1，不為0 結束
	}
};

