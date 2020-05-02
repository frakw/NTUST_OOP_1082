#include <iostream>
using namespace std;
int gcd(int, int);
int main() {
    int a, b;
    while (cin >> a) {
        cin >> b;
        cout << gcd(a, b) << endl;
    }
    return 0;
}

int gcd(int a,int b) {//輾轉相除法
    if (b) {
        return gcd(b, a % b);
    }
    else {
        return a;
    }
}