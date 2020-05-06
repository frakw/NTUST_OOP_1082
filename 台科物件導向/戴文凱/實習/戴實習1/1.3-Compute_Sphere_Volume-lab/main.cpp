#include <iostream>
#include <cmath>
#include <cstdio>
using namespace std;
const double PI = 3.14159265358979323846;
int main() {
    double radius;
    while (cin >> radius) {
        printf("%.6f\n", (pow(radius, 3.0) * 4 * PI) / 3.0f);
    }
    return 0;
}