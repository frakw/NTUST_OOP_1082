#include <iostream>
#include <string>
#include <cmath>
using std::endl;
int main() {
	while (!std::cin.eof()) {
		int square_len;
		std::string input;
		std::cin >> input;
		square_len = std::ceil(std::sqrt(input.length()));
		for (int i = 0;i < square_len;i++) 
		{
			for (int j = 0;j < square_len && (j* square_len + i)< input.length();j++) 
			{
				std::cout << input[j * square_len + i];
			}
			std::cout << endl;
		}
	}
    return 0;
}