#include<sstream>
#include<iostream>
#include<iomanip>

using namespace std;

#define SEG_LEN 8
#define SEG_VAL 100000000
class BigInt {

private:
	int len = 0; // array length
	unsigned int* buffer = nullptr; // integer buffer (20 digits per segment)
	bool isNegative = false;
	bool isInfinite = false;

	// string to integer buffer
	void stoi(string& s) {
		// init properties
		isNegative = false;
		isInfinite = false;

		// if input is negative.
		isNegative = (s[0] == '-');
		if (isNegative) {
			s.erase(s.begin());
		}
		int digits = s.size();

		// calculate needed segment size.
		len = (digits / SEG_LEN) + 1;

		// allocate buffer.
		if (buffer != nullptr) {
			delete[] buffer;
		}
		buffer = new unsigned int[len];

		for (int i = 0; i < len; i++) {
			buffer[i] = 0;

			int idx = s.size() - i * SEG_LEN - 1;
			int mul = 1;
			for (int j = 0; j < SEG_LEN && idx >= 0; j++) {
				buffer[i] += (s[idx] - '0') * mul;
				mul *= 10;
				idx -= 1;
			}
		}

	}

public:
	friend istream& operator>>(istream& stream, BigInt& b) {
		string str;
		stream >> str;

		b.stoi(str);

		return stream;
	}
	friend ostream& operator<<(ostream& stream, BigInt b) {
		stringstream ss;

		bool isZero = true;
		// output infinite
		if (b.isInfinite) {
			ss << "Inf";
			isZero = false;
		}
		// output digits
		else {
			for (int i = b.len - 1; i > 0; i--) {
				if (isZero) {
					if (b.buffer[i] > 0) {
						isZero = false;
						ss << b.buffer[i];
					}
				}
				else {
					ss << setfill('0') << setw(SEG_LEN) << b.buffer[i];
				}
			}

			if (isZero) {
				if (b.buffer[0] > 0)
				{
					isZero = false;
					ss << b.buffer[0];
				}
				else {
					// is zero, only output zero
					stream << 0;
				}
			}
			else {
				ss << setfill('0') << setw(SEG_LEN) << b.buffer[0];
			}
		}

		if (!isZero) {
			// output negative
			if (b.isNegative) {
				stream << '-';
			}
			stream << ss.str();
		}

		return stream;
	}
	
	BigInt() {
		len = 0; // array length
		buffer = nullptr; // integer buffer (20 digits per segment)
		isNegative = false;
		isInfinite = false;
	}

	BigInt(int num) {
		len = 1;
		if (buffer != nullptr)
			delete[] buffer;
		buffer = new unsigned int[1];

		buffer[0] = abs(num);
		isInfinite = false;
		isNegative = (num < 0);
	}

	BigInt(const BigInt& big) {
		len = big.len;
		if (buffer != nullptr)
			delete[] buffer;
		buffer = new unsigned int[len];

		for (int i = 0; i < len; i++) {
			buffer[i] = big.buffer[i];
		}

		isInfinite = big.isInfinite;
		isNegative = big.isNegative;
	}

	BigInt operator/ (int num) {
		BigInt tmp(*this);
		tmp /= num;
		return tmp;
	}

	BigInt& operator /=(int num) {

		if (num == 0) {
			isInfinite = true;
			return *this;
		}

		// xor with negative (+, +) => +, (-, -) => +
		isNegative ^= (num < 0);

		unsigned long long divisor = abs(num);
		unsigned long long dividend = 0;
		unsigned long long quotient = 0;

		for (int i = len - 1; i >= 0; i--) {
			dividend += buffer[i];

			quotient = dividend / divisor;

			buffer[i] = quotient;

			dividend -= (quotient * divisor);
			dividend *= SEG_VAL;
		}

		return *this;
	}
};