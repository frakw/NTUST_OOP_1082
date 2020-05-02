#include <iostream>
int main() {
	unsigned long long seconds, min, hr;
	while (!std::cin.eof()) {
		std::cin >> seconds;
		hr = seconds / 3600;
		seconds %= 3600;
		min = seconds / 60;
		seconds %= 60;
		std::cout << hr << " hours " << min << " minutes and " << seconds << " seconds" << std::endl;
	}
	return 0;
}